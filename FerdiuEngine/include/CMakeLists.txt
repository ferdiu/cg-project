
# add headers to SOURCES TODO: add more hpp files here
set(PUBLIC_HEADERS
    ${INC_DIR}/Scene.hpp
    ${INC_DIR}/Texture.hpp
    ${INC_DIR}/Material.hpp
    ${INC_DIR}/Vertex.hpp
    ${INC_DIR}/Shader.hpp
    ${INC_DIR}/Components/MeshRenderer.hpp
    ${INC_DIR}/Components/Component.hpp
    ${INC_DIR}/Components/Physic/SphereCollider.hpp
    ${INC_DIR}/Components/Physic/Bounds.hpp
    ${INC_DIR}/Components/Physic/RigidBody.hpp
    ${INC_DIR}/Components/Physic/Collider.hpp
    ${INC_DIR}/Components/Physic/BoxCollider.hpp
    ${INC_DIR}/Components/Camera.hpp
    ${INC_DIR}/Components/SphereRenderer.hpp
    ${INC_DIR}/Components/Renderer.hpp
    ${INC_DIR}/Components/CubeRenderer.hpp
    ${INC_DIR}/Components/Transform.hpp
    ${INC_DIR}/utils/BitMapFile.hpp
    ${INC_DIR}/utils/GLMatrices.hpp
    ${INC_DIR}/utils/GLMatricesStack.hpp
    ${INC_DIR}/utils/Debug.hpp
    ${INC_DIR}/GameObject.hpp
)

set(MAIN_API_HEADER ${INC_DIR}/FerdiuEngine.hpp)
