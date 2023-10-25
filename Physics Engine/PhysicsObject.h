#pragma once
#include "Model.h"


enum PhysicsType
{
	SPHERE,
	AABB
};


struct cAABB
{

	cAABB()
	{
	}
	cAABB(glm::vec3 minV, glm::vec3 maxV)
	{
		this->minV = minV;
		this->maxV = maxV;
	}
	~cAABB() {}
	glm::vec3 minV;
	glm::vec3 maxV;
	void calculateAABB(std::vector<Vertex>& vertices)
	{

		if (vertices.size()==0)
		{
			minV = glm::vec3(0);
			maxV = glm::vec3(0);
			return;
		}

		/*minV = vertices[0].vPos;
		maxV = vertices[0].vPos;*/

		for (const Vertex& vertex : vertices)
		{
			minV.x = min(minV.x,vertex.vPos.x);   // min of x
			minV.y = min(minV.y,vertex.vPos.y);    // min of y
			minV.z = min(minV.z,vertex.vPos.z);   // min of z

			maxV.x = max(maxV.x, vertex.vPos.x);   // max of x
			maxV.y = max(maxV.y, vertex.vPos.y);    // max of y
			maxV.z = max(maxV.z, vertex.vPos.z);   // max of z

		}

		std::cout << "MinV : " << minV.x << " , " << minV.y << " , " << minV.z << std::endl;
		std::cout << "MaxV : " << maxV.x << " , " << maxV.y << " , " << maxV.z << std::endl;
	}
};


struct cSphere
{
	cSphere(glm::vec3 position, float radius)
	{
		this->center = position;
		this->radius = radius;
	}
	cSphere()
	{

	}

	~cSphere() {}
	glm::vec3 center;
	float radius;
	void calculateSphere(std::vector<Vertex>& vertices)
	{
		glm::vec3 minV;
		glm::vec3 maxV;
		if (vertices.empty())
		{
			center = glm::vec3(0);
			radius = 0;
			return;
		}

		minV = vertices[0].vPos;
		maxV = vertices[0].vPos;
		for (const Vertex& vertex : vertices)
		{
			minV.x = min(minV.x, vertex.vPos.x);   // min of x
			minV.y = min(minV.y, vertex.vPos.y);    // min of y
			minV.z = min(minV.z, vertex.vPos.z);   // min of z

			maxV.x = max(maxV.x, vertex.vPos.x);   // max of x
			maxV.y = max(maxV.y, vertex.vPos.y);    // max of y
			maxV.z = max(maxV.z, vertex.vPos.z);   // max of z

		}

		float maxDistance = 0;

		for (const Vertex& vertex : vertices)
		{
			float distance = glm::length(vertex.vPos - center);
			if (distance > maxDistance) {
				maxDistance = distance;
			}
		}

		center = (minV + maxV) * 0.5f;
		radius = maxDistance;

		std::cout << "Sphere Centre : " << center.x << " , " << center.y << " , " << center.z << std::endl;
		std::cout << "Radius : " << radius<< std::endl;
	}

};



class PhysicsObject
{
public:
	PhysicsObject();
	PhysicsObject(ModelLoad* model);
	~PhysicsObject();

	ModelLoad* model;
	PhysicsType physicsType;
	bool isKinematic;
	void update(float deltatime);
	cAABB UpdateAABB();
	cSphere UpdateSphere();
	bool checkCollision(const PhysicsObject& other);
	glm::vec3 velocity;
	glm::vec3 acceleration;
	float gravityValue;
	void Initialize(bool isKinematic);
	cAABB aabb;
	cSphere sphereShape;


};

