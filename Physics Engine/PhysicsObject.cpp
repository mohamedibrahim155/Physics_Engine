#include "PhysicsObject.h"





PhysicsObject::PhysicsObject(ModelLoad* model)
{
	this->model = model;
	acceleration = glm::vec3(0.0f);
	

}

PhysicsObject::PhysicsObject()
{

	acceleration = glm::vec3(0.0f);

}

PhysicsObject::~PhysicsObject()
{
	//delete model;
}

void PhysicsObject::update(float deltatime)
{
	glm::vec3 gravity(0.0f, -9.81f* gravityValue, 0.0f);
	acceleration = gravity;
	velocity += acceleration * deltatime;
	model->transform.position += velocity * deltatime;
	

}
cAABB  PhysicsObject:: UpdateAABB()
{

	//cAABB temp;

	glm::vec3 originalMinV = aabb.minV;
	glm::vec3 originalMaxV = aabb.maxV;
	glm::mat4 transformMatrix = model->transform.getModelMatrix();
	glm::vec4 transformedMinV = transformMatrix * glm::vec4(originalMinV, 1.0f);
	glm::vec4 transformedMaxV = transformMatrix * glm::vec4(originalMaxV, 1.0f);

	return  cAABB(glm::vec3(transformedMinV), glm::vec3(transformedMaxV));
	
}

cSphere PhysicsObject::UpdateSphere()
{
	glm::vec3 originalCenter = sphereShape.center;
	float orginalRadius = sphereShape.radius;
	glm::mat4 transformMatrix = model->transform.getModelMatrix();
	glm::vec4 transformedCenter = transformMatrix * glm::vec4(originalCenter, 1.0f);

	glm::mat4 scaleMatrix = glm::mat4(1.0f); // Initialize the scale matrix
	scaleMatrix[0][0] = model->transform.scale.x;
	scaleMatrix[1][1] = model->transform.scale.y;
	scaleMatrix[2][2] = model->transform.scale.z;

	float maxScale = max(model->transform.scale.x, max(model->transform.scale.y, model->transform.scale.z));
	float updatedRadius = orginalRadius * maxScale;

	return cSphere(glm::vec3(transformedCenter), updatedRadius);
}

void PhysicsObject::Initialize(bool isKinematic)
{
	this->isKinematic = isKinematic;
	if (this->isKinematic)
	{
		gravityValue = 0;
	}
	else
	{
		gravityValue = 0.01f;
	}
	if (physicsType == AABB)
	{
		aabb.calculateAABB(model->ListofMeshesInthisModel[0].Vertices);

	}
	if (physicsType == SPHERE)
	{
		sphereShape.calculateSphere(model->ListofMeshesInthisModel[0].Vertices);
	}
	
}
