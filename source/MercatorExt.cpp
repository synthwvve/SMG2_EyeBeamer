#include "MercatorExt.h"

static f32 calcLocalHeight(const MercatorTransformCube* pCube, const TVec3f& rPos) {
    TVec3f localPos;
    MR::calcCubeLocalPos(&localPos, pCube, rPos);
    return localPos.y;
}

static void convertTransAndRotate(const MercatorTransformCube* pCube, TVec3f* pPos, TPos3f* pRotation,
                                  const TVec3f& rPos, bool applyInverse) {
    TVec2f uv;
    pCube->calcUV(&uv, rPos);

    TVec3f point;
    f32 radius = pCube->getSphereRadius() * MR::cos(uv.y);
    point.x = radius * MR::sin(uv.x);
    point.y = pCube->getSphereRadius() * MR::sin(uv.y);
    point.z = radius * MR::cos(uv.x);

    TVec3f offset(point);
    MR::normalize(&offset);
    offset *= calcLocalHeight(pCube, rPos);
    point.add(offset);

    TVec3f up(0.0f, 1.0f, 0.0f);
    TVec3f front;
    if (MR::isSameDirection(point, up, 0.01f)) {
        front.set(0.0f, 0.0f, MR::sign(point.y));
    } else {
        TVec3f side;
        PSVECCrossProduct(point, up, side);
        PSVECCrossProduct(point, side, front);
    }

    MR::makeMtxUpFront(pRotation, point, front);

    pCube->mZonePlacementMtx.mult(point, point);
    TMtx34f rotation(pCube->mZonePlacementMtx);
    rotation.mMtx[0][3] = 0.0f;
    rotation.mMtx[1][3] = 0.0f;
    rotation.mMtx[2][3] = 0.0f;

    if (applyInverse) {
        TMtx34f inverse;
        inverse.invert(rotation);
        pRotation->concat(*pRotation, inverse);
    }

    pRotation->concat(rotation, *pRotation);
    pPos->set(point);
}

void MR::convertMercatorPlaneToSphereTransAndRotate(TVec3f* pPos, TPos3f* pRotation, const TVec3f& rPos, bool applyInverse) {
    convertTransAndRotate(getMercatorCube(), pPos, pRotation, rPos, applyInverse);
}

void MR::convertMercatorPlaneToSphereTransAndRotate(TVec3f* pPos, TVec3f* pRotation, const TVec3f& rPos, bool applyInverse) {
    TPos3f rotation;
    convertTransAndRotate(getMercatorCube(), pPos, &rotation, rPos, applyInverse);
    TVec3f angles;
    rotation.getEulerXYZ(angles);
    pRotation->set(57.29577951308232f * angles.x, 57.29577951308232f * angles.y, 57.29577951308232f * angles.z);
}
