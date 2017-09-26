/*
 * game_main.h
 *
 *  Created on: 21-Sep-2017
 *      Author: sree
 */

#ifndef GAME_MAIN_H_
#define GAME_MAIN_H_

#include <time.h>
#include <unistd.h>
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
	selection = 0;
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
			SoundEngine->play2D("sound/menu_enter.wav");
			break;
		}
		if(stepFrame > 0.1f){
			if(glfwGetKey(window->window, GLFW_KEY_DOWN) == GLFW_PRESS){
				selection = (selection + 1) % 3;
				SoundEngine->play2D("sound/drop_beep.wav");
			}
			if(glfwGetKey(window->window, GLFW_KEY_UP) == GLFW_PRESS){
				selection--;
				SoundEngine->play2D("sound/drop_beep.wav");
				if(selection == -1)
					selection = 2;
			}
			stepFrame = 0.0f;
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
	switch(player.data.stage){
	case STAGE_1:
		if(glm::distance(glm::vec3(0), camera.Position) < 16.0f){
			tetrisStart = true;
			cameraMove = false;
			//put some transition here
			player.data.stage = TETRIS;
			SoundEngine->play2D("sound/menu_enter.wav");
			setUpSkyBox(tetrisSkybox);
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
