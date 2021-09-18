//
// Created by Supakorn on 9/17/2021.
//

#pragma once
#include "common.h"
#include "Buffers.h"

#define VEC4_ALIGN alignas(sizeof(glm::vec4))

struct UniformObjects
{
    VEC4_ALIGN
    float time;

    VEC4_ALIGN
    glm::mat4 proj;

    VEC4_ALIGN
    glm::mat4 view;

    VEC4_ALIGN
    glm::mat4 model;

    static VkDescriptorSetLayoutBinding descriptorSetLayout(uint32_t binding=0)
    {
        VkDescriptorSetLayoutBinding uboLayout = {};
        uboLayout.binding = binding;
        uboLayout.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        uboLayout.descriptorCount = 1;
        uboLayout.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
        uboLayout.pImmutableSamplers = nullptr;

        return uboLayout;
    }
};

template<typename TUniformBuffer=UniformObjects>
struct UniformObjBuffer : Buffers::Buffer
{
    UniformObjBuffer() = default;
    ~UniformObjBuffer() override = default;

    UniformObjBuffer(
            VkDevice* dev,
            VkPhysicalDevice const& physicalDev,
            Buffers::optUint32Set const& usedQueues = nullopt,
            VkFlags const& additionalFlags = 0,
            VkMemoryPropertyFlags const& memoryFlags = 0

    ) : Buffer(dev, physicalDev, sizeof(TUniformBuffer),
               VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | additionalFlags,
               memoryFlags, usedQueues)
    {
    }

    UniformObjBuffer(UniformObjBuffer const&) = delete;
    UniformObjBuffer& operator=(UniformObjBuffer const&) = delete;

    UniformObjBuffer(UniformObjBuffer&& ubo) noexcept : Buffers::Buffer(std::move(ubo)) {}

    UniformObjBuffer& operator= (UniformObjBuffer&& ubo) noexcept
    {
        Buffers::Buffer::operator=(std::move(ubo));

        return *this;
    }

    VkResult loadData(TUniformBuffer const& data, uint32_t const& offset=0)
    {
        return Buffers::Buffer::loadData(&data, offset);
    }
};