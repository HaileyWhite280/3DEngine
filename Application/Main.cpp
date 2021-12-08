#include "Engine.h"
#include "Graphics/Shader.h"
#include "Graphics/Program.h"

#include <glad\glad.h>
#include <sdl.h>
#include <glm/vec3.hpp>
#include <glm/vec3.hpp>

#include <iostream>

int main(int argc, char** argv)
{
	// create engine
	std::unique_ptr<nc::Engine> engine = std::make_unique<nc::Engine>();
	engine->Startup();
	engine->Get<nc::Renderer>()->Create("OpenGL", 800, 600);

	nc::SeedRandom(static_cast<unsigned int>(time(nullptr)));
	nc::SetFilePath("../resources");

	// create scene
	std::unique_ptr<nc::Scene> scene = std::make_unique<nc::Scene>();
	scene->engine = engine.get();

	// load scene
	rapidjson::Document document;
	bool success = nc::json::Load("scenes/main.scn", document);
	scene->Read(document);


	//// create camera
	//{
	//	auto actor = CREATE_ENGINE_OBJECT(Actor);
	//	actor->name = "camera";
	//	actor->transform.position = glm::vec3{ 0, 0, 5 };

	//	{
	//		auto component = CREATE_ENGINE_OBJECT(CameraComponent);
	//		component->SetPerspective(45.0f, 800.0f / 600.0f, 0.01f, 100.0f);
	//		actor->AddComponent(std::move(component));
	//	}
	//	{
	//		auto component = CREATE_ENGINE_OBJECT(FreeCameraController);
	//		component->speed = 8;
	//		component->sensitivity = 0.1f;
	//		actor->AddComponent(std::move(component));
	//	}
	//	
	//	scene->AddActor(std::move(actor));
	//}

	//// create model
	//{
	//	auto actor = CREATE_ENGINE_OBJECT(Actor);
	//	actor->name = "model";
	//	actor->transform.position = glm::vec3{ 0 };
	//	actor->transform.scale = glm::vec3{ 1 };

	//	auto component = CREATE_ENGINE_OBJECT(ModelComponent);
	//	component->model = engine->Get<nc::ResourceSystem>()->Get<nc::Model>("models/ogre.obj");
	//	component->material = engine->Get<nc::ResourceSystem>()->Get<nc::Material>("materials/wood.mtl", engine.get());

	//	actor->AddComponent(std::move(component));
	//	scene->AddActor(std::move(actor));
	//}

	// create light
	{
		auto actor = CREATE_ENGINE_OBJECT(Actor);
		actor->name = "light";
		actor->transform.position = glm::vec3{ 4 };

		auto component = CREATE_ENGINE_OBJECT(LightComponent);
		component->ambient = glm::vec3{ 0.2f };
		component->diffuse = glm::vec3{ 1 };
		component->specular = glm::vec3{ 1 };

		actor->AddComponent(std::move(component));
		scene->AddActor(std::move(actor));
	}

	glm::vec3 translate{ 0 };
	float angle = 0;

	float time = 0;

	bool quit = false;
	while (!quit)
	{
		SDL_Event event;
		SDL_PollEvent(&event);

		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				quit = true;
			}
		}

		SDL_PumpEvents();
		engine->Update();
		scene->Update(engine->time.deltaTime);

		time += engine->time.deltaTime;

		// update actor
		auto actor = scene->FindActor("model");
		if (actor != nullptr)
		{
			actor->transform.rotation = actor->transform.rotation + glm::vec3{ 0, engine->time.deltaTime, 0 };
			auto component = actor->GetComponent<nc::ModelComponent>();
		}

		//update shader
		auto shader = engine->Get<nc::ResourceSystem>()->Get<nc::Program>("Shaders/phong_normal.shdr");
		if (shader)
		{
			shader->Use();
			//shader->SetUniform("time", time);
			//shader->SetUniform("uv.tiling", glm::vec2{ 10 });
			//shader->SetUniform("uv.offset", glm::vec2{ 0, time });

			//shader->SetUniform("strength", (std::sin(time * 4) + 1.0f) * 0.5f);
			//shader->SetUniform("radius", 0.5f);
		}

		//// update actor
		//auto actor = scene->FindActor("light");
		//if (actor != nullptr)
		//{
		//	glm::mat3 rotation = glm::rotate(engine->time.deltaTime, glm::vec3{ 0, 0, 1 });
		//	actor->transform.position = actor->transform.position * rotation;
		//}

		engine->Get<nc::Renderer>()->BeginFrame();

		scene->Draw(nullptr);

		engine->Get<nc::Renderer>()->EndFrame();
	}

	return 0;
}
