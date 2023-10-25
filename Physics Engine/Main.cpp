#include <iostream>
#include "OpenGL_Common.h"
#include<fstream>
#include<sstream>
#include <filesystem>

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include<glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>

#include "Shader.h"

#include"Model.h";
//#include "Mesh.h";
#include "Camera.h"
#include "LightManager.h"
#include "Texture.h"
//#include<windows.h>
#include "PhysicsObject.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#pragma region Variables Declaration
const int WIDTH_WINDOW = 1200;
const int HEIGHT_WINDOW = 800;
std::string Game_Title = "Model Loading";
Camera camera(glm::vec3(0.0f, 0.0f, 10));
#pragma endregion

float deltaTime = 0.0f;
float lastFrame = 0.0f;

float lastX = 0.0f;
float lastY = 0.0f;
bool firstMouse = true;

bool switchCamera = false;
bool switchToPointLight = false;

glm::vec3 currentLight(1.0f, 0.0f, 1.0f);
glm::vec3 spotlightPos(1.0f, 0.0f, 1.0f);
glm::vec3 PointLightPos(-1.0f, 0.0f, 1.0f);

static const char* DIFFUSE = "DIFFUSE";
static const char* SPECULAR = "SPECULAR";

struct ModelInfo
{
	ModelLoad model;
	glm::mat4 transformation;
};
std::vector<ModelInfo> models;
std::vector<ModelLoad*> modelsLoaded;
std::vector<ModelLoad*> modelsLoadedFromFile;
unsigned int loadTexture(char const* path);
void MoveModels(ModelInfo& model, glm::vec3 position);

void ReadData(const std::string& fileName, std::vector<ModelLoad>& models, std::vector<Light>& lights, std::vector<Camera>& cameras);
bool WriteModelData(std::string saveFileName);
std::vector<ModelLoad*> ReadModelData(const std::string& filename);

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);


	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{

		if (switchCamera)
		{
			float velocity = camera.MovementSpeed * deltaTime;
			currentLight += camera.Front * velocity;
		}
		else
		{
			camera.ProcessKeyboard(FORWARD, deltaTime);
		}


	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{

		if (switchCamera)
		{
			float velocity = camera.MovementSpeed * deltaTime;
			currentLight -= camera.Front * velocity;
		}
		else
		{
			camera.ProcessKeyboard(BACKWARD, deltaTime);
		}
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		if (switchCamera)
		{
			float velocity = camera.MovementSpeed * deltaTime;
			currentLight -= camera.Right * velocity;
		}
		else
		{
			camera.ProcessKeyboard(LEFT, deltaTime);

		}

	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		if (switchCamera)
		{
			float velocity = camera.MovementSpeed * deltaTime;
			currentLight += camera.Right * velocity;

		}
		else
		{
			camera.ProcessKeyboard(RIGHT, deltaTime);

		}

	}

	if (switchToPointLight)
	{
		PointLightPos = currentLight;
	}
	else
	{
		spotlightPos = currentLight;
	}
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		camera.ProcessMouseMovement(xoffset, yoffset);
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_V && action == GLFW_PRESS)
	{
		switchCamera = !switchCamera;
		std::cout << "Value of swtich camera : " << switchCamera << std::endl;
	}
	if (key == GLFW_KEY_P && action == GLFW_PRESS)
	{

		switchToPointLight = !switchToPointLight;
		std::cout << "Value of swtich pointLight : " << switchToPointLight << std::endl;
		if (switchToPointLight)
		{
			currentLight = PointLightPos;
		}
		else
		{
			currentLight = spotlightPos;

		}
	}


	if (key == GLFW_KEY_O && action == GLFW_PRESS)
	{
		WriteModelData("Save.txt");

	}
	if (key == GLFW_KEY_I && action == GLFW_PRESS)
	{
		// modelsLoadedFromFile = ReadModelData("Save.txt");

		//// Printing the read data to verify
		// for (const auto& model : modelsLoaded)
		// {
		//	 std::cout << "Model_path:" << model->modelPath << std::endl;
		//	 std::cout << "Position: { " << model->transform.position.x << ", " << model->transform.position.y << ", " << model->transform.position.z << " }" << std::endl;
		//	 std::cout << "Rotation: { " << model->transform.rotation.x << ", " << model->transform.rotation.y << ", " << model->transform.rotation.z << " }" << std::endl;
		//	 std::cout << "Scale: { " << model->transform.scale.x << ", " << model->transform.scale.y << ", " << model->transform.scale.z << " }" << std::endl;
		// }



		// ModelLoad* LightModel = new ModelLoad();
		// LightModel->diffuseTexture.LoadTexture("Models/SpecSphere/Sphere 1_Sphere__Diffuse.png", DIFFUSE);
		// LightModel->specularTexture.LoadTexture("Models/SpecSphere/Sphere 1_Sphere__Specular.png", SPECULAR);
		// LightModel->LoadModel(modelsLoaded[0]->modelPath);
		// LightModel->transform.position.x= -5.0f;
		// modelsLoaded.push_back(LightModel);

		std::vector<ModelLoad> models;
		std::vector<Light> lights;
		std::vector<Camera> cameras;

		std::string fileName = "SimpleData.txt"; // Replace with the path of your file
		ReadData(fileName, models, lights, cameras);

		// Printing the read data to verify
		for (const auto& model : models) {
			std::cout << "Model_name: " << model.modelName << std::endl;
			std::cout << "Model_Path: " << model.modelPath << std::endl;
			std::cout << "Position: { " << model.transform.position.x << ", " << model.transform.position.y << ", " << model.transform.position.z << " }" << std::endl;
			std::cout << "Rotation: { " << model.transform.rotation.x << ", " << model.transform.rotation.y << ", " << model.transform.rotation.z << " }" << std::endl;
			std::cout << "Scale: { " << model.transform.scale.x << ", " << model.transform.scale.y << ", " << model.transform.scale.z << " }" << std::endl;
		}

		for (const auto& light : lights) {
			std::cout << "Model_Path: " << light.lightModel->modelPath << std::endl;
			std::cout << "Light_Type: " << light.lightType << std::endl;
			std::cout << "Position: { " << light.lightModel->transform.position.x << ", " << light.lightModel->transform.position.y << ", " << light.lightModel->transform.position.z << " }" << std::endl;
			std::cout << "Rotation: { " << light.lightModel->transform.rotation.x << ", " << light.lightModel->transform.rotation.y << ", " << light.lightModel->transform.rotation.z << " }" << std::endl;
			std::cout << "Scale: { " << light.lightModel->transform.scale.x << ", " << light.lightModel->transform.scale.y << ", " << light.lightModel->transform.scale.z << " }" << std::endl;
		}

		for (const auto& camera : cameras) {
			std::cout << "Position: { " << camera.Position.x << ", " << camera.Position.y << ", " << camera.Position.z << " }" << std::endl;
			//std::cout << "Rotation: { " << camera.rotation.x << ", " << camera.rotation.y << ", " << camera.rotation.z << " }" << std::endl;
			//std::cout << "Scale: { " << camera.scale.x << ", " << camera.scale.y << ", " << camera.scale.z << " }" << std::endl;
		}


	}

}



static bool CheckCOllisionAABBvsAABB(const cAABB& a, const cAABB& b)
{
	if (a.maxV[0] < b.minV[0] || a.minV[0] > b.maxV[0]) return false;
	if (a.maxV[1] < b.minV[1] || a.minV[1] > b.maxV[1]) return false;
	if (a.maxV[2] < b.minV[2] || a.minV[2] > b.maxV[2]) return false;

	return true;
}
static bool checkSphereCollision(const cSphere& sphere1, const cSphere& sphere2) 
{
	float distance = glm::distance(sphere1.center, sphere2.center);
	float sumRadii = sphere1.radius + sphere2.radius;
	return distance <= sumRadii;
}

static bool CheckSphereAABBCollision(const cSphere& sphere, const cAABB& aabb) {
	glm::vec3 closestPoint;

	// Find the closest point on the AABB to the sphere
	closestPoint.x = max(aabb.minV.x, min(sphere.center.x, aabb.maxV.x));
	closestPoint.y = max(aabb.minV.y, min(sphere.center.y, aabb.maxV.y));
	closestPoint.z = max(aabb.minV.z, min(sphere.center.z, aabb.maxV.z));

	// Calculate squared distance between the sphere center and the closest point on the AABB
	float lengthSquared = glm::dot(closestPoint - sphere.center, closestPoint - sphere.center);

	// Check for collision
	return lengthSquared < (sphere.radius * sphere.radius);
}


int main()
{

	if (!glfwInit())
	{
		// Initialization failed
		std::cout << "Initialization Failed";
		exit(EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	GLFWwindow* window = glfwCreateWindow(WIDTH_WINDOW, HEIGHT_WINDOW, Game_Title.c_str(), NULL, NULL);
	if (!window)
	{
		// Window or OpenGL context creation failed
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, key_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}


	ShaderClass LightShader("VertexShader.vert", "FragmentShader.frag");
	ShaderClass defaultShader("Light_VertexShader.vert", "Light_FragmentShader.frag");






	ModelLoad* sphere1 = new ModelLoad();
	sphere1->diffuseTexture.LoadTexture("Models/SpecSphere/Sphere 1_Sphere__Diffuse.png", DIFFUSE);
	sphere1->specularTexture.LoadTexture("Models/SpecSphere/Sphere 1_Sphere__Specular.png", SPECULAR);
	sphere1->LoadModel("Sphere_1_unit_Radius.ply");
	sphere1->transform.position.y += 3;
	sphere1->transform.scale =glm::vec3(0.3f);
	modelsLoaded.push_back(sphere1);


	ModelLoad* sphere2= new ModelLoad();
	sphere2->diffuseTexture.LoadTexture("Models/SpecSphere/Sphere 1_Sphere__Diffuse.png", DIFFUSE);
	sphere2->specularTexture.LoadTexture("Models/SpecSphere/Sphere 1_Sphere__Specular.png", SPECULAR);
	sphere2->LoadModel("Sphere_1_unit_Radius.ply");
	sphere2->transform.scale = glm::vec3(1);
	modelsLoaded.push_back(sphere2);


	ModelLoad* sphere3 = new ModelLoad();
	sphere3->diffuseTexture.LoadTexture("Models/SpecSphere/Sphere 1_Sphere__Diffuse.png", DIFFUSE);
	sphere3->specularTexture.LoadTexture("Models/SpecSphere/Sphere 1_Sphere__Specular.png", SPECULAR);
	sphere3->LoadModel("Sphere_1_unit_Radius.ply");
	sphere3->transform.scale = glm::vec3(0.1f);
	modelsLoaded.push_back(sphere3);

	ModelLoad* sphere4 = new ModelLoad();
	sphere4->diffuseTexture.LoadTexture("Models/SpecSphere/Sphere 1_Sphere__Diffuse.png", DIFFUSE);
	sphere4->specularTexture.LoadTexture("Models/SpecSphere/Sphere 1_Sphere__Specular.png", SPECULAR);
	sphere4->LoadModel("Sphere_1_unit_Radius.ply");
	sphere4->transform.scale = glm::vec3(0.1f);
	modelsLoaded.push_back(sphere4);

	ModelLoad* plane = new ModelLoad();
	plane->diffuseTexture.LoadTexture("Models/SpecSphere/Sphere 1_Sphere__Diffuse.png", DIFFUSE);
	plane->specularTexture.LoadTexture("MModels/SpecSphere/Sphere 1_Sphere__Diffuse.png", SPECULAR);
	plane->LoadModel("Models/Plane/floor.obj");
	//plane->transform.position.y = -1;
	plane->transform.scale =glm::vec3(1);
	modelsLoaded.push_back(plane);



	LightManager lightManager;
	Light directionLight;
	directionLight.lightType = DIRECTION_LIGHT;
	directionLight.lightModel = sphere2;


	Light PointLight;
	PointLight.lightType = POINT_LIGHT;
    PointLight.lightModel = sphere2;

	Light spotLight;
	spotLight.lightType = SPOT_LIGHT;
	spotLight.lightModel = sphere2;
	spotLight.direction = glm::vec3(0, 0, -1);




	lightManager.AddNewLight(directionLight);
	lightManager.AddNewLight(PointLight);
	lightManager.AddNewLight(spotLight);
	lightManager.SetUniforms(defaultShader.ID);


	PhysicsObject speherePhysics(sphere1);
	speherePhysics.physicsType = SPHERE;
	speherePhysics.Initialize(false);

	//push back
	

	PhysicsObject speherePhysics2(plane);
	speherePhysics2.physicsType = AABB;
	speherePhysics2.Initialize(true);
	
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		ProcessInput(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);


		defaultShader.UseProgram();
		lightManager.UpdateUniformValues(defaultShader.ID);
		defaultShader.SetFloat("material.shininess", 52.f);
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)WIDTH_WINDOW / (float)HEIGHT_WINDOW, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		defaultShader.SetMat4("projection", projection);
		defaultShader.SetMat4("view", view);
		//sphere2->DrawMeshes(defaultShader);
		sphere1->DrawMeshes(defaultShader);
		sphere3->DrawMeshes(defaultShader);
		sphere4->DrawMeshes(defaultShader);
		//sphere2->DrawMeshes(defaultShader);
		plane->DrawMeshes(defaultShader);

		sphere3->transform.position = speherePhysics.UpdateSphere().center;
		//sphere4->transform.position = speherePhysics.UpdateSphere().radius;

	
		speherePhysics.update(deltaTime);
		//speherePhysics.UpdateAABB();
		speherePhysics2.update(deltaTime);


		/*speherePhysics.UpdateAABB(speherePhysics.model->transform);
		speherePhysics2.UpdateAABB(speherePhysics2.model->transform);*/
	

		//for (size_t i = 0; i < length; i++)
		//{
		//	//for (size_t i = 0; i < length; i++)
		//	{
		//		//if
		//		//if i <j
		//		if (CheckCOllisionAABBvsAABB(speherePhysics.UpdateAABB(), speherePhysics2.UpdateAABB()))
		//		{
		//			std::cout << "Collided ......." << std::endl;
		//		}

		//	}
		//}
		//

		if (CheckSphereAABBCollision(speherePhysics.UpdateSphere(), speherePhysics2.UpdateAABB()))
		{
			std::cout << "Collided ......." << std::endl;
		}
		

		glfwSwapBuffers(window);
		glfwPollEvents();

	}



	delete	sphere1;

	modelsLoaded.clear();
	glfwTerminate();
	return 0;

}

