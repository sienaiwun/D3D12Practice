
#pragma once
#include "GameCore.h"


using namespace Math;
using namespace GameCore;

namespace Voxel
{
	struct  VoxelRegion 
	{
        VoxelRegion() {}
        VoxelRegion(const glm::ivec3& minPos, const glm::ivec3& extent, float voxelSize)
            :minPos(minPos), extent(extent), voxelSize(voxelSize) {}

        /**
         * Returns the minimum position of the clip region in world coordinates.
         */
        Dagon::Vec3f getMinPosWorld() const { return Dagon::Vec3f(minPos) * voxelSize; }

        /**
        * Returns the maximum position of the clip region in world coordinates.
        */
        Dagon::Vec3f getMaxPosWorld() const { return Dagon::Vec3f(getMaxPos()) * voxelSize; }

        /**
        * Returns the minimum position of the clip region in image coordinates using toroidal addressing.
        * Note: The % operator is expected to be defined by the C++11 standard.
        */
        glm::ivec3 getMinPosImage(const glm::ivec3& imageSize) const { return ((minPos % imageSize) + imageSize) % imageSize; }

        /**
        * Returns the maximum position of the clip region in image coordinates using toroidal addressing.
        * Note: The % operator is expected to be defined by the C++11 standard.
        */
        glm::ivec3 getMaxPosImage(const glm::ivec3& imageSize) const { return ((getMaxPos() % imageSize) + imageSize) % imageSize; }

        /**
         * Returns the maximum position in local voxel coordinates.
         */
        glm::ivec3 getMaxPos() const { return minPos + extent; }

        /**
         * Returns the extent in world coordinates.
         */
        Dagon::Vec3f getExtentWorld() const { return Dagon::Vec3f(extent) * voxelSize; }

        Dagon::Vec3f getCenterPosWorld() const { return getMinPosWorld() + getExtentWorld() * 0.5f; }

        VoxelRegion toPrevLevelRegion() const
        {
            return VoxelRegion(minPos * 2, extent * 2, voxelSize / 2.0f);
        }

        VoxelRegion toNextLevelRegion() const
        {
            // extent + 1 is used to make sure that the upper bound is computed
            return VoxelRegion(minPos / 2, (extent + 1) / 2, voxelSize * 2.0f);
        }

        glm::ivec3 minPos;       // The minimum position in local voxel coordinates
        glm::ivec3 extent{ 0 };  // The extent of the region in local voxel coordinates 
        float voxelSize{ 0.0f }; // Voxel size in world coordinates
	};
}
