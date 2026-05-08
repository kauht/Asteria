#include "modules.hpp"

namespace modules {

    void Initialize() {
        client = GetModuleHandleA("client.dll");
        if (!client) {
            io::println("Failed to get client.dll module handle");
            return;
        }
        engine2 = GetModuleHandleA("engine2.dll");
        if (!engine2) {
            io::println("Failed to get engine2.dll module handle");
            return;
        }
        inputsystem = GetModuleHandleA("inputsystem.dll");
        if (!inputsystem) {
            io::println("Failed to get inputsystem.dll module handle");
            return;
        }
        materialsystem2 = GetModuleHandleA("materialsystem2.dll");
        if (!materialsystem2) {
            io::println("Failed to get materialsystem2.dll module handle");
            return;
        }
        networksystem = GetModuleHandleA("networksystem.dll");
        if (!networksystem) {
            io::println("Failed to get networksystem.dll module handle");
            return;
        }
        panorama = GetModuleHandleA("panorama.dll");
        if (!panorama) {
            io::println("Failed to get panorama.dll module handle");
            return;
        }
        particles = GetModuleHandleA("particles.dll");
        if (!particles) {
            io::println("Failed to get particles.dll module handle");
            return;
        }
        pulse_system = GetModuleHandleA("pulse_system.dll");
        if (!pulse_system) {
            io::println("Failed to get pulse_system.dll module handle");
            return;
        }
        rendersystemdx11 = GetModuleHandleA("rendersystemdx11.dll");
        if (!rendersystemdx11) {
            io::println("Failed to get rendersystemdx11.dll module handle");
            return;
        }
        resourcesyystem = GetModuleHandleA("resourcesystem.dll");
        if (!resourcesyystem) {
            io::println("Failed to get resourcesystem.dll module handle");
            return;
        }
        scenesystem = GetModuleHandleA("scenesystem.dll");
        if (!scenesystem) {
            io::println("Failed to get scenesystem.dll module handle");
            return;
        }
        schemasystem = GetModuleHandleA("schemasystem.dll");
        if (!schemasystem) {
            io::println("Failed to get schemasystem.dll module handle");
            return;
        }
        server = GetModuleHandleA("server.dll");
        if (!server) {
            io::println("Failed to get server.dll module handle");
            return;
        }
        tier0 = GetModuleHandleA("tier0.dll");
        if (!tier0) {
            io::println("Failed to get tier0.dll module handle");
            return;
        }
        worldrenderer = GetModuleHandleA("worldrenderer.dll");
        if (!worldrenderer) {
            io::println("Failed to get worldrenderer.dll module handle");
            return;
        }
    }

    void Shutdown() {
        client = {};
        engine2 = {};
        inputsystem = {};
        materialsystem2 = {};
        networksystem = {};
        panorama = {};
        particles = {};
        pulse_system = {};
        rendersystemdx11 = {};
        resourcesyystem = {};
        scenesystem = {};
        schemasystem = {};
        server = {};
        tier0 = {};
        worldrenderer = {};
    }

}
