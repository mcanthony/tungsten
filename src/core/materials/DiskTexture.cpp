#include "DiskTexture.hpp"

#include "sampling/SampleWarp.hpp"

#include "math/MathUtil.hpp"

namespace Tungsten {

rapidjson::Value DiskTexture::toJson(Allocator &allocator) const
{
    rapidjson::Value v = Texture::toJson(allocator);
    v.AddMember("type", "disk", allocator);
    return std::move(v);
}

bool DiskTexture::isConstant() const
{
    return false;
}

Vec3f DiskTexture::average() const
{
    return Vec3f(PI*0.25f);
}

Vec3f DiskTexture::minimum() const
{
    return Vec3f(0.0f);
}

Vec3f DiskTexture::maximum() const
{
    return Vec3f(1.0f);
}

Vec3f DiskTexture::operator[](const Vec<float, 2> &uv) const
{
    return (uv - Vec2f(0.5f)).lengthSq() < 0.25f ? Vec3f(1.0f) : Vec3f(0.0f);
}

void DiskTexture::derivatives(const Vec2f &/*uv*/, Vec2f &derivs) const
{
    derivs = Vec2f(0.0f);
}

void DiskTexture::makeSamplable(TextureMapJacobian /*jacobian*/)
{
}

Vec2f DiskTexture::sample(const Vec2f &uv) const
{
    return SampleWarp::uniformDisk(uv).xy()*0.5f + 0.5f;
}

float DiskTexture::pdf(const Vec2f &uv) const
{
    return (uv - Vec2f(0.5f)).lengthSq() < 0.25f ? SampleWarp::uniformDiskPdf()*4.0f : 0.0f;
}

}
