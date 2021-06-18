#include "include/House.h"

House::House()
{
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

void House::createHouse(glm::vec3 center, GLint shaderProgram)
{

	this->center = center;
	glBindVertexArray(VAO);

	// land 
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->floorTex);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, center - glm::vec3(0.0f, (this->height + this->thickness)/2.0 , 0.0f));
	model = glm::scale(model, glm::vec3(4*this->length, this->thickness, 4*this->breadth));
	GLuint transformLoc1 = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindTexture(GL_TEXTURE_2D, 0);

	// right one
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->wallTex);
	model = glm::mat4(1.0f);
	model = glm::translate(model, center + glm::vec3((this->length - this->thickness) / 2.0, 0.0f, this->breadth/2.0f));
	model = glm::scale(model, glm::vec3(this->thickness, this->height, this->breadth));
	transformLoc1 = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// right two
	model = glm::mat4(1.0f);
	model = glm::translate(model, center + glm::vec3((this->length - this->thickness) / 2.0, 0.0f, -this->breadth/2.0f));
	model = glm::scale(model, glm::vec3(this->thickness, this->height, this->breadth));
	transformLoc1 = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	
	// left one contains door
	model = glm::mat4(1.0f);
	model = glm::translate(model, center + glm::vec3(-(this->length - this->thickness) / 2.0, 0.0f, this->breadth*31/32.0f));
	model = glm::scale(model, glm::vec3(this->thickness, this->height, this->breadth/16.0));
	transformLoc1 = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model = glm::mat4(1.0f);
	model = glm::translate(model, center + glm::vec3(-(this->length - this->thickness) / 2.0, 0.0f, this->breadth*9/32.0f));
	model = glm::scale(model, glm::vec3(this->thickness, this->height, this->breadth*9/16.0));
	transformLoc1 = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model = glm::mat4(1.0f);
	model = glm::translate(model, center + glm::vec3(-(this->length - this->thickness) / 2.0, this->height*5/16.0, this->breadth*3/4.0f));
	model = glm::scale(model, glm::vec3(this->thickness, this->height*3/8.0, this->breadth*3/8.0));
	transformLoc1 = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// left two
	model = glm::mat4(1.0f);
	model = glm::translate(model, center + glm::vec3(-(3*this->length - this->thickness) / 2.0, 0.0f, -this->breadth/2.0f));
	model = glm::scale(model, glm::vec3(this->thickness, this->height, this->breadth));
	transformLoc1 = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// table
	glBindTexture(GL_TEXTURE_2D, this->wood);
	model = glm::mat4(1.0f);
	model = glm::translate(model, center + glm::vec3(-(2.5*this->length - this->thickness) / 2.0, -this->height/3 + this->thickness*3, -7*this->breadth/8.0f));
	model = glm::scale(model, glm::vec3(this->thickness*2, this->height/2.5, this->thickness*2));
	transformLoc1 = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model = glm::mat4(1.0f);
	model = glm::translate(model, center + glm::vec3(-(2.0*this->length - this->thickness) / 2.0, -this->height/3 + this->thickness*3, -5*this->breadth/8.0f));
	model = glm::scale(model, glm::vec3(this->thickness*2, this->height/2.5, this->thickness*2));
	transformLoc1 = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model = glm::mat4(1.0f);
	model = glm::translate(model, center + glm::vec3(-(2.5*this->length - this->thickness) / 2.0, -this->height/3 + this->thickness*3, -5*this->breadth/8.0f));
	model = glm::scale(model, glm::vec3(this->thickness*2, this->height/2.5, this->thickness*2));
	transformLoc1 = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model = glm::mat4(1.0f);
	model = glm::translate(model, center + glm::vec3(-(2.0*this->length - this->thickness) / 2.0, -this->height/3 + this->thickness*3, -7*this->breadth/8.0f));
	model = glm::scale(model, glm::vec3(this->thickness*2, this->height/2.5, this->thickness*2));
	transformLoc1 = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model = glm::mat4(1.0f);
	model = glm::translate(model, center + glm::vec3(-(2.25*this->length - this->thickness) / 2.0, -this->height/8.0f, -6*this->breadth/8.0f));
	model = glm::scale(model, glm::vec3((this->length/4)+2*this->thickness, this->thickness*5, this->thickness*2 + this->breadth/4));
	transformLoc1 = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindTexture(GL_TEXTURE_2D, 0);

	// sofa table
	glBindTexture(GL_TEXTURE_2D, this->wood);
	model = glm::mat4(1.0f);
	model = glm::translate(model, center + glm::vec3(-(this->length/8.0f+this->thickness), -this->height/3.0f - this->thickness*3, 1*this->breadth/8.0f));
	model = glm::scale(model, glm::vec3(this->thickness*2, this->height/4.0f, this->thickness*2));
	transformLoc1 = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model = glm::mat4(1.0f);
	model = glm::translate(model, center + glm::vec3(this->length/8.0f+this->thickness, -this->height/3.0f - this->thickness*3, 3*this->breadth/8.0f));
	model = glm::scale(model, glm::vec3(this->thickness*2, this->height/4.0f, this->thickness*2));
	transformLoc1 = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model = glm::mat4(1.0f);
	model = glm::translate(model, center + glm::vec3(-(this->length/8.0f+this->thickness), -this->height/3.0f - this->thickness*3, 3*this->breadth/8.0f));
	model = glm::scale(model, glm::vec3(this->thickness*2, this->height/4.0f, this->thickness*2));
	transformLoc1 = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model = glm::mat4(1.0f);
	model = glm::translate(model, center + glm::vec3(this->length/8.0f+this->thickness, -this->height/3.0f - this->thickness*3, 1*this->breadth/8.0f));
	model = glm::scale(model, glm::vec3(this->thickness*2, this->height/4.0f, this->thickness*2));
	transformLoc1 = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindTexture(GL_TEXTURE_2D, 0);

	// sofa
	glBindTexture(GL_TEXTURE_2D, this->sofa);

	model = glm::mat4(1.0f);
	model = glm::translate(model, center + glm::vec3((this->length/4)-1*this->thickness, -this->height/3 - this->thickness*2.0f, 6*this->breadth/8.0f));
	model = glm::scale(model, glm::vec3(this->thickness*6, this->height/3.5, this->thickness*2 + this->breadth/4));
	transformLoc1 = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model = glm::mat4(1.0f);
	model = glm::translate(model, center + glm::vec3(-((this->length/4)-1*this->thickness), -this->height/3 - this->thickness*2.0f, 6*this->breadth/8.0f));
	model = glm::scale(model, glm::vec3(this->thickness*6, this->height/3.5, this->thickness*2 + this->breadth/4));
	transformLoc1 = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model = glm::mat4(1.0f);
	model = glm::translate(model, center + glm::vec3(0.0f, -this->height/4.0f-this->thickness*2, 7*this->breadth/8.0f));
	model = glm::scale(model, glm::vec3((this->length/2)+2*this->thickness, this->height/2.5, this->thickness*5));
	transformLoc1 = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model = glm::mat4(1.0f);
	model = glm::translate(model, center + glm::vec3(0.0f, -this->height/2.5f, 6*this->breadth/8.0f));
	model = glm::scale(model, glm::vec3((this->length/2)-6*this->thickness, this->height/5.0f, this->thickness*2 + this->breadth/4));
	transformLoc1 = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindTexture(GL_TEXTURE_2D, 0);


	// cupboard
	glBindTexture(GL_TEXTURE_2D, this->wood);
	model = glm::mat4(1.0f);
	model = glm::translate(model, center + glm::vec3(-(-0.25*this->length - this->thickness) / 2.0, -this->height/3 + this->thickness*3, -7*this->breadth/8.0f));
	model = glm::scale(model, glm::vec3(this->length/4, this->height/2.5, this->thickness*2));
	transformLoc1 = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model = glm::mat4(1.0f);
	model = glm::translate(model, center + glm::vec3(-(-0.5*this->length - this->thickness) / 2.0, -this->height/3 + this->thickness*3, -6*this->breadth/8.0f));
	model = glm::scale(model, glm::vec3(this->thickness*2, this->height/2.5, this->breadth/4+this->thickness*2));
	transformLoc1 = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model = glm::mat4(1.0f);
	model = glm::translate(model, center + glm::vec3(-(0.0*this->length - this->thickness) / 2.0, -this->height/3 + this->thickness*3, -6*this->breadth/8.0f));
	model = glm::scale(model, glm::vec3(this->thickness*2, this->height/2.5, this->breadth/4+this->thickness*2));
	transformLoc1 = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model = glm::mat4(1.0f);
	model = glm::translate(model, center + glm::vec3(-(-0.25*this->length - this->thickness) / 2.0, -this->height/8+this->thickness*2, -6*this->breadth/8.0f));
	model = glm::scale(model, glm::vec3((this->length/4)+2*this->thickness, this->thickness, this->thickness*2 + this->breadth/4));
	transformLoc1 = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model = glm::mat4(1.0f);
	model = glm::translate(model, center + glm::vec3(-(-0.25*this->length - this->thickness) / 2.0, -this->height/8-this->thickness*8, -6*this->breadth/8.0f));
	model = glm::scale(model, glm::vec3((this->length/4)+2*this->thickness, this->thickness, this->thickness*2 + this->breadth/4));
	transformLoc1 = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model = glm::mat4(1.0f);
	model = glm::translate(model, center + glm::vec3(-(-0.25*this->length - this->thickness) / 2.0, -this->height/8-this->thickness*18, -6*this->breadth/8.0f));
	model = glm::scale(model, glm::vec3((this->length/4)+2*this->thickness, this->thickness, this->thickness*2 + this->breadth/4));
	transformLoc1 = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindTexture(GL_TEXTURE_2D, 0);

	// lamp
	model = glm::mat4(1.0f);
	model = glm::translate(model, center + glm::vec3(-this->length/2.0f, (this->height-this->thickness) / 2.0f - this->length/30.0f, -this->breadth + this->thickness*10));
	model = glm::scale(model, glm::vec3(this->thickness, this->length/15.0f, this->thickness));
	transformLoc1 = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model = glm::mat4(1.0f);
	model = glm::translate(model, center + glm::vec3(-this->length/2.0f, (this->height-this->thickness) / 2.0f - this->length/15.0f, -this->breadth + this->thickness*10));
	model = glm::scale(model, glm::vec3(this->thickness*5.0f, this->thickness/2, this->thickness*5.0f));
	transformLoc1 = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model = glm::mat4(1.0f);
	model = glm::translate(model, center + glm::vec3(-this->length/2.0f, (this->height-this->thickness) / 2.0f - 2*this->length/15.0f, -this->breadth + this->thickness*10));
	model = glm::scale(model, glm::vec3(this->thickness*5.0f, this->thickness/2, this->thickness*5.0f));
	transformLoc1 = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// top one
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindTexture(GL_TEXTURE_2D, this->roofTex);

	model = glm::mat4(1.0f);
	model = glm::translate(model, center + glm::vec3(0.0f, (this->height-this->thickness) / 2.0f, this->breadth / 2.0f));
	model = glm::scale(model, glm::vec3(this->length, this->thickness, this->breadth));
	transformLoc1 = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// top two
	model = glm::mat4(1.0f);
	model = glm::translate(model, center + glm::vec3(0.0f, (this->height-this->thickness) / 2.0f, -this->breadth / 2.0f));
	model = glm::scale(model, glm::vec3(this->length, this->thickness, this->breadth));
	transformLoc1 = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// top three
	model = glm::mat4(1.0f);
	model = glm::translate(model, center + glm::vec3(-this->length, (this->height-this->thickness) / 2.0f, -this->breadth / 2.0f));
	model = glm::scale(model, glm::vec3(this->length, this->thickness, this->breadth));
	transformLoc1 = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindTexture(GL_TEXTURE_2D, 0);

	glBindTexture(GL_TEXTURE_2D, this->wallTex);
	// back one
	model = glm::mat4(1.0f);
	model = glm::translate(model, center + glm::vec3(0.0f, 0.0f, -(2*this->breadth - this->thickness) / 2.0));
	model = glm::scale(model, glm::vec3(this->length, this->height, this->thickness));
	transformLoc1 = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// back two
	model = glm::mat4(1.0f);
	model = glm::translate(model, center + glm::vec3(-this->length, 0.0f, -(2*this->breadth - this->thickness) / 2.0));
	model = glm::scale(model, glm::vec3(this->length, this->height, this->thickness));
	transformLoc1 = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);


	// front one contains window
	model = glm::mat4(1.0f);
	model = glm::translate(model, center + glm::vec3(-(11*this->length) / 32.0f, 0.0f, (2*this->breadth - this->thickness) / 2.0));
	model = glm::scale(model, glm::vec3((5*this->length) / 16.0f, this->height, this->thickness));
	transformLoc1 = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model = glm::mat4(1.0f);
	model = glm::translate(model, center + glm::vec3((11*this->length) / 32.0f, 0.0f, (2*this->breadth - this->thickness) / 2.0));
	model = glm::scale(model, glm::vec3((5*this->length) / 16.0f, this->height, this->thickness));
	transformLoc1 = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model = glm::mat4(1.0f);
	model = glm::translate(model, center + glm::vec3(0.0f, this->height / 3.0f, (2*this->breadth - this->thickness) / 2.0));
	model = glm::scale(model, glm::vec3((3*this->length) / 8.0f, this->height / 3.0f , this->thickness));
	transformLoc1 = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model = glm::mat4(1.0f);
	model = glm::translate(model, center + glm::vec3(0.0f, -this->height / 3.0f, (2*this->breadth - this->thickness) / 2.0));
	model = glm::scale(model, glm::vec3((3*this->length) / 8.0f, this->height / 3.0f, this->thickness));
	transformLoc1 = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// front two contains sliding window
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->windowTex);
	if (isOpen && openWindow < 50) openWindow+=0.5;
	else if (openWindow > 0 && !isOpen) openWindow-=0.5;
	model = glm::mat4(1.0f);
	model = glm::translate(model, center + glm::vec3(-3*this->length/4.0f - (openWindow*(this->length)/100.0f), 0.0f, -this->thickness/2.0));
	model = glm::scale(model, glm::vec3(this->length / 2.0, this->height, this->thickness));
	transformLoc1 = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model = glm::mat4(1.0f);
	model = glm::translate(model, center + glm::vec3(-5*this->length/4.0f, 0.0f, this->thickness/2.0));
	model = glm::scale(model, glm::vec3(this->length / 2.0, this->height, this->thickness));
	transformLoc1 = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// door
	model = glm::mat4(1.0f);
	if (isOpen1 && openDoor < 50) openDoor+=0.5;
	else if (openDoor > 0 && !isOpen1) openDoor-=0.5;
	model = glm::translate(model, center + glm::vec3(-(this->length - this->thickness) / 2.0, -this->height*3/16.0, this->breadth*3/4.0f));
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, this->breadth*3/16.0));
	model = glm::rotate(model, glm::radians(openDoor), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -this->breadth*3/16.0));
	model = glm::scale(model, glm::vec3(this->thickness, this->height*5/8.0, this->breadth*3/8.0));
	transformLoc1 = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// front window
	model = glm::mat4(1.0f);
	model = glm::translate(model, center + glm::vec3(0.0f, 0.0f, (2*this->breadth - this->thickness) / 2.0));
	model = glm::scale(model, glm::vec3((3*this->length) / 8.0f, this->height / 3.0f, this->thickness));
	transformLoc1 = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// sofa table's top part
	model = glm::mat4(1.0f);
	model = glm::translate(model, center + glm::vec3(0.0f, -this->height/5.0f-6*this->thickness, 2*this->breadth/8.0f));
	model = glm::scale(model, glm::vec3((this->length/4)+2*this->thickness, this->thickness*2, this->thickness*2 + this->breadth/4));
	transformLoc1 = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// lamp's part
	model = glm::mat4(1.0f);
	model = glm::translate(model, center + glm::vec3(-this->length/2.0f-this->thickness*2.5f, (this->height-this->thickness) / 2.0f - this->length/10.0f, -this->breadth + this->thickness*10));
	model = glm::scale(model, glm::vec3(this->thickness/2.0f, this->length/15.0f, this->thickness*5.0f));
	transformLoc1 = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model = glm::mat4(1.0f);
	model = glm::translate(model, center + glm::vec3(-this->length/2.0f+this->thickness*2.5f, (this->height-this->thickness) / 2.0f - this->length/10.0f, -this->breadth + this->thickness*10));
	model = glm::scale(model, glm::vec3(this->thickness/2.0f, this->length/15.0f, this->thickness*5.0f));
	transformLoc1 = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model = glm::mat4(1.0f);
	model = glm::translate(model, center + glm::vec3(-this->length/2.0f, (this->height-this->thickness) / 2.0f - this->length/10.0f, -this->breadth + this->thickness*7.5));
	model = glm::scale(model, glm::vec3(this->thickness*5.0f,this->length/15.0f,this->thickness/2));
	transformLoc1 = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model = glm::mat4(1.0f);
	model = glm::translate(model, center + glm::vec3(-this->length/2.0f, (this->height-this->thickness) / 2.0f - this->length/10.0f, -this->breadth + this->thickness*12.5));
	model = glm::scale(model, glm::vec3(this->thickness*5.0f,this->length/15.0f,this->thickness/2));
	transformLoc1 = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindVertexArray(0);
}

void House::createLight(GLint lampProgram)
{
	// light source
	glm::mat4 model = glm::mat4(1.0f);
	glBindVertexArray(VAO);
	model = glm::translate(model, glm::vec3(0.0f, 15.2f, 0.0f));
	model = glm::scale(model, glm::vec3(3.0f, 3.0f, 10.0f));
	GLuint transformLoc1 = glGetUniformLocation(lampProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);


	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-this->length, 15.2f, -this->breadth / 2.0f));
	model = glm::scale(model, glm::vec3(3.0f, 3.0f, 10.0f));
	transformLoc1 = glGetUniformLocation(lampProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void House::createLight1(GLint lampProgram)
{
	// light source
	glm::mat4 model = glm::mat4(1.0f);
	glBindVertexArray(VAO);
	model = glm::translate(model, glm::vec3(-this->length/2.0f, (this->height-this->thickness) / 2.0f - this->length/10.0f, -this->breadth + this->thickness*10));
	model = glm::scale(model, glm::vec3(this->thickness*4.0f,this->length/15.0f-this->thickness*2,this->thickness*4.0f));
	GLuint transformLoc1 = glGetUniformLocation(lampProgram, "model");
	transformLoc1 = glGetUniformLocation(lampProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}


House::~House()
{
}
