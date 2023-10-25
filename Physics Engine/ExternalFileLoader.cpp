

#include <string>
#include <fstream>
#include "Model.h";
#include <vector>
#include <iostream>
#include <iostream>
#include <sstream>
#include"Light.h"
#include "Camera.h"
struct ModelValues
{
	std::string Path;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

};

 extern std::vector<ModelLoad*> modelsLoaded;

bool WriteModelData(std::string saveFileName)
{

	std::ofstream writeFile(saveFileName.c_str());

	for (size_t i = 0; i < modelsLoaded.size(); i++)
	{
		writeFile << "Model_path: " << modelsLoaded[i]->modelPath <<  std::endl;
		writeFile << "position: { " << modelsLoaded[i]->transform.position.x << ","<< modelsLoaded[i]->transform.position.y << "," <<modelsLoaded[i]->transform.position.z <<" }" << std::endl;
		writeFile << "Rotation: { " << modelsLoaded[i]->transform.rotation.x << ","<< modelsLoaded[i]->transform.rotation.y << "," <<modelsLoaded[i]->transform.rotation.z <<" }" << std::endl;
		writeFile << "Scale: { " << modelsLoaded[i]->transform.scale.x << ","<< modelsLoaded[i]->transform.scale.y << "," <<modelsLoaded[i]->transform.scale.z <<" }" << std::endl;
	}

	return false;
}

// Function to read the data
std::vector<ModelLoad*> ReadModelData(const std::string& fileName)
{
    std::ifstream file(fileName);
    std::vector<ModelLoad*> models;
    std::string line;
    ModelLoad* currentModel = new ModelLoad();

    while (std::getline(file, line)) 
    {
        std::istringstream iss(line);
        std::string token;
        iss >> token;
        if (token == "Model_path")
        {

            if (line.find("#Model") != line.npos)
            {
                continue;
            }
            if (!currentModel->modelPath.empty()) 
            {
                models.push_back(currentModel);
                currentModel = new ModelLoad();
            }
            std::string path;
            std::getline(iss, path);
            currentModel->modelPath = path;
        }
        else if (token == "position:") {
            char brace;
            char comma;
            iss >> brace >> currentModel->transform.position.x >> comma >> currentModel->transform.position.y >> comma >> currentModel->transform.position.z >> brace;
        }
        else if (token == "Rotation:") {
            char brace;
            char comma;
            iss >> brace >> currentModel->transform.rotation.x >> comma >> currentModel->transform.rotation.y >> comma >> currentModel->transform.rotation.z >> brace;
        }
        else if (token == "Scale:") {
            char brace;
            char comma;
            iss >> brace >> currentModel->transform.scale.x >> comma >> currentModel->transform.scale.y >> comma >> currentModel->transform.scale.z >> brace;
        }
    }
    if (!currentModel->modelPath.empty()) {
        models.push_back(currentModel);
    }
    file.close();
    return models;
}


void ReadFileBasedOntype(const std::string& fileName)
{
    std::ifstream file(fileName);
    std::string line;
    std::vector<ModelLoad*> listOfModels;
    ModelLoad* currentmodel=nullptr;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string token;
        iss >> token;
       
        if (token == "#Model")
        {
            std::cout << "Found Model.. " << std::endl;
            continue;
        }
        if (token =="position:")
        {
            char space;
            iss >> space;
        }
    }

}

void ReadData(const std::string& fileName, std::vector<ModelLoad>& models, std::vector<Light>& lights, std::vector<Camera>& cameras) 
{
    std::cout << "Entering readingData " << std::endl;
    std::ifstream file(fileName);
    std::string line;
    std::string currentSection;

    while (std::getline(file, line)) {
        if (line.empty()) 
        {
            continue;
        }
        std::istringstream iss(line);
        std::string token;
        iss >> token;
        if (token == "#Model") {
            currentSection = "Model";
            models.emplace_back(ModelLoad());
        }
        else if (token == "#light") {
            currentSection = "Light";
            lights.emplace_back(Light());
            iss >> token; // Read light type
 
            if (token =="point")
            {
                lights.back().lightType = POINT_LIGHT;
            }
            if (token == "spot")
            {
                lights.back().lightType = SPOT_LIGHT;
            }
            if (token == "direction")
            {
                lights.back().lightType = DIRECTION_LIGHT;
            }
        }
        else if (token == "#camera") {
            currentSection = "Camera";
            cameras.emplace_back(Camera());
        }
        else if (token == "Model_name" && currentSection == "Model") {
            std::getline(iss, models.back().modelName);
        }
        else if (token == "Model_Path" && (currentSection == "Model" || currentSection == "Light")) {
            std::getline(iss, currentSection == "Model" ? models.back().modelPath : lights.back().lightModel->modelPath);
        }
        else if (token == "Light_Type" && currentSection == "Light")
        {
            std::string lightType;
            iss >> lightType;
            if (lightType==" point")
            {
                lights.back().lightType = POINT_LIGHT;
            }
            if (lightType == " spot")
            {
                lights.back().lightType = SPOT_LIGHT;
            
            }
            if (lightType == " direction")
            {
                lights.back().lightType = DIRECTION_LIGHT;

            }
        }
        else if (token == "position:") 
        {
            char brace;
            char comma;
            if (currentSection == "Model") {
                iss >> brace >> models.back().transform.position.x >> comma >> models.back().transform.position.y >> comma >> models.back().transform.position.z >> brace;
            }
            else if (currentSection == "Light") {
                iss >> brace >> lights.back().lightModel->transform.position.x >> comma >> lights.back().lightModel->transform.position.y >> comma >> lights.back().lightModel->transform.position.z >> brace;
            }
            else if (currentSection == "Camera") {
                iss >> brace >> cameras.back().Position.x >> comma >> cameras.back().Position.y >> comma >> cameras.back().Position.z >> brace;
            }
        }
        else if (token == "Rotation:") {
            char brace;
            char comma;
            if (currentSection == "Model") {
                iss >> brace >> models.back().transform.rotation.x >> comma >> models.back().transform.rotation.y >> comma >> models.back().transform.rotation.z >> brace;
            }
            else if (currentSection == "Light") {
                iss >> brace >> lights.back().lightModel->transform.rotation.x >> comma >> lights.back().lightModel->transform.rotation.y >> comma >> lights.back().lightModel->transform.rotation.z >> brace;
            }
            else if (currentSection == "Camera")
            {
                glm::vec3 cameraRot;
               // cameras.back().rotation.x
                iss >> brace >> cameraRot.x >> comma >> cameraRot.y >> comma >> cameraRot.z >> brace;
            }
        }
        else if (token == "Scale:") {
            char brace;
            char comma;
            if (currentSection == "Model") {
                iss >> brace >> models.back().transform.scale.x >> comma >> models.back().transform.scale.y >> comma >> models.back().transform.scale.z >> brace;
            }
            else if (currentSection == "Light") {
                iss >> brace >> lights.back().lightModel->transform.scale.x >> comma >> lights.back().lightModel->transform.scale.y >> comma >> lights.back().lightModel->transform.scale.z >> brace;
            }
            else if (currentSection == "Camera") 
            {
                glm::vec3 cameraScale;
                //cameras.back().scale.x
                iss >> brace >> cameraScale.x >> comma >> cameraScale.y >> comma >> cameraScale.z >> brace;
            }
        }
    }
    file.close();
    std::cout << "ended readingData " << std::endl;
}