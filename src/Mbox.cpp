#include "include/Mbox.h"

Mbox::Mbox(GLboolean d)
{
	if (d) soundEngine = createIrrKlangDevice();
	if (!d) 
	{
		length = 0.1f;
		breadth = 0.1f;
		height = 0.1f;
	}
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(6 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mbox::createBox(glm::vec3 center, GLint shaderProgram)
{
	if (isOpen) 
	{
		if (openAngle < 135.0f) openAngle += 0.5f;
		if (openAngle == 134.0f && !isMusic) 
		{
				soundEngine->play2D("bin/audio/sample.mp3", GL_TRUE);
				isMusic = GL_TRUE;
		}
	}
	else 
	{
		if (openAngle > 0) openAngle-= 0.5f;
		if (openAngle == 1.0f) 
		{
			soundEngine->setAllSoundsPaused();
			isMusic = GL_FALSE;
		}
	}

	//std::cout << openAngle << std::endl;

	this->center = center;
	glBindVertexArray(VAO);

	// right one
	if (isPoint) glBindTexture(GL_TEXTURE_2D, this->innerTex);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, this->center);
	model = glm::rotate(model, glm::radians(this->cen), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, -this->center);
	model = glm::translate(model, center + glm::vec3((this->length - this->thickness) / 2.0, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(this->thickness, this->height, this->breadth));
	GLuint transformLoc1 = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	
	// left one
	model = glm::mat4(1.0f);
	model = glm::translate(model, this->center);
	model = glm::rotate(model, glm::radians(this->cen), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, -this->center);
	model = glm::translate(model, center + glm::vec3(-(this->length - this->thickness) / 2.0, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(this->thickness, this->height, this->breadth));
	transformLoc1 = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// top one
	model = glm::mat4(1.0f);
	model = glm::translate(model, this->center);
	model = glm::rotate(model, glm::radians(this->cen), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, -this->center);
	model = glm::translate(model, center + glm::vec3(0.0f, (this->height - this->thickness) / 2.0, -this->breadth / 2.0f));
	model = glm::rotate(model, glm::radians(-openAngle), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, this->breadth / 2.0f));
	model = glm::scale(model, glm::vec3(this->length, this->thickness, this->breadth));
	transformLoc1 = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// bottom one
	model = glm::mat4(1.0f);
	model = glm::translate(model, this->center);
	model = glm::rotate(model, glm::radians(this->cen), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, -this->center);
	model = glm::translate(model, center + glm::vec3(0.0f, -(this->height - this->thickness) / 2.0, 0.0f));
	model = glm::scale(model, glm::vec3(this->length, this->thickness, this->breadth));
	transformLoc1 = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// back one
	model = glm::mat4(1.0f);
	model = glm::translate(model, this->center);
	model = glm::rotate(model, glm::radians(this->cen), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, -this->center);
	model = glm::translate(model, center + glm::vec3(0.0f, 0.0f, -(this->breadth - this->thickness) / 2.0));
	model = glm::scale(model, glm::vec3(this->length, this->height, this->thickness));
	transformLoc1 = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	if (isPoint) glBindTexture(GL_TEXTURE_2D, 0);

	// front one
	if (isPoint) glBindTexture(GL_TEXTURE_2D, this->texture1);
	model = glm::mat4(1.0f);
	model = glm::translate(model, this->center);
	model = glm::rotate(model, glm::radians(this->cen), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, -this->center);
	model = glm::translate(model, center + glm::vec3(0.0f, 0.0f, (this->breadth - this->thickness) / 2.0));
	model = glm::scale(model, glm::vec3(this->length, this->height, this->thickness));
	transformLoc1 = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	if (isPoint) glBindTexture(GL_TEXTURE_2D, 0);

	// dance floor 
	if (isPoint) glBindTexture(GL_TEXTURE_2D, this->texture2);
	model = glm::mat4(1.0f);
	model = glm::translate(model, this->center);
	model = glm::rotate(model, glm::radians(this->cen), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, -this->center);
	model = glm::translate(model, center + glm::vec3(0.0f, ((this->height - this->thickness) * (openAngle - 67.5)/ 135.0), 0.0f));
	model = glm::scale(model, glm::vec3(this->length-2*this->thickness, this->thickness, this->breadth-2*this->thickness));
	transformLoc1 = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	if (isPoint) glBindTexture(GL_TEXTURE_2D, 0);

	glBindVertexArray(0);
}


Mbox::~Mbox()
{
}
