/*
 * game_main.h
 *
 *  Created on: 21-Sep-2017
 *      Author: sree
 */

#ifndef GAME_MAIN_H_
#define GAME_MAIN_H_

#include <time.h>

void displayMenu(Window *window, Shader shader, Shader simpleDepthShader, Shader skyboxShader){
	camera.Position = glm::vec3(0.0f, 5.0f, 0.0f);
	camera.Pitch = -90.0f;
	camera.updateCameraVectors();
	cameraMove = false;
	cameraMouseMove = false;
	try{
		delete img;
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	img = new Model("cyborg/menu.obj");
	shader.setFloat("transition", 1.0f);
	while (!glfwWindowShouldClose(window->window)) {
		glfwWaitEvents();
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		stepFrame = stepFrame + deltaTime;

		// render
		// ------
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if(glfwGetKey(window->window, GLFW_KEY_ENTER) == GLFW_PRESS){
			break;
		}

		renderDepth(simpleDepthShader, MENU);
		renderScene(shader, MENU);
		glfwSwapBuffers(window->window);

	}
	shader.setFloat("transition", 1.0f);
	cameraMouseMove = true;
}

void game(Window *window, Shader shader, Shader simpleDepthShader, Shader skyboxShader) {
	//Check Positions
	//std::cout << glm::distance(glm::vec3(0), camera.Position) << std::endl;
	switch(stage){
	case STAGE_1:
		if(glm::distance(glm::vec3(0), camera.Position) < 20.0f){
			tetrisStart = true;
			cameraMove = false;
			//put some transition here
			stage = TETRIS;
			runTetris(window, shader, simpleDepthShader, skyboxShader);
		}
		break;
	default:
		std::cout << "Default Stage\n";
	}
}


void fadeOutMusic(irrklang::ISound* sound, float duration){
	time_t start = time(0);
	while(1){
		double now = difftime( time(0), start);
		sound->setVolume(1.0f - now / duration);
		if(sound->getVolume() < 0)
			break;
	}
	sound->stop();
}

#endif /* GAME_MAIN_H_ */
