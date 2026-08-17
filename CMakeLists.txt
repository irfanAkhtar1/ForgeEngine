set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
cmake_minimum_required(VERSION 3.20)
project(ForgeEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

add_executable(ForgeEngine
    src/Window.cpp
    src/Renderer.cpp
    src/Application.cpp
    src/Texture.cpp
    src/Text.cpp
    src/Input.cpp
    src/Camera.cpp
    src/AssetManager.cpp
    src/Sprite.cpp
    src/Animation.cpp
    src/PhysicsBody.cpp
    src/Collider.cpp
    src/TileMap.cpp
    src/Entity.cpp
    src/AudioManager.cpp
    src/SceneManager.cpp


    sandbox/GameOverScene.cpp
    sandbox/main.cpp
    sandbox/GameScene.cpp
    sandbox/Coin.cpp
    sandbox/Player.cpp
    sandbox/MovingPlatform.cpp

)

target_include_directories(ForgeEngine PRIVATE include)

target_link_libraries(ForgeEngine PRIVATE
    SDL2::SDL2main
    SDL2::SDL2
    SDL2_image::SDL2_image
    SDL2_ttf::SDL2_ttf
    SDL2_mixer::SDL2_mixer
)
