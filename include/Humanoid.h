#pragma once
#include <iostream>
#include <utility>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>

/**
 * Body parts names
 */
enum BodyPart
{
	Head,
	Neck,
	Torso,
	LeftHand,
	RightArm,
	RightHand,
	LeftThigh,
	LeftLeg,
	RightThigh,
	RightLeg,
	Plate,
	LeftArm
};

/**
 * Basic building block of graphical human
 */
struct Atom
{
	GLuint VAO, VBO;
	GLfloat vertices[288] = {
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,

		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f};
	glm::vec3 center;
	Atom()
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid *)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid *)(3 * sizeof(GL_FLOAT)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid *)(6 * sizeof(GL_FLOAT)));
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
};

/**
 * Graphical Body part
 */
class BodyParts
{
public:
	Atom *matter;
	BodyPart type;
	GLuint texture;
	glm::vec3 pCentroid = glm::vec3(0.0f);
	glm::vec3 shift = glm::vec3(0.0f);
	glm::vec3 point_Inflne1 = glm::vec3(0.0f);
	glm::vec3 point_Inflne2 = glm::vec3(0.0f);
	glm::vec3 point_Inflne3 = glm::vec3(0.0f);
	glm::vec3 point_Inflne4 = glm::vec3(0.0f);
	GLfloat angle0 = 0.0f, angle1 = 0.0f, angle2 = 0.0f, cen = 0.0f;
	GLfloat length, breadth, height;
	glm::vec3 center, center1;
	std::vector<std::pair<BodyParts *, glm::vec3>> children;
	GLint ShaderProgram;
	BodyParts(GLfloat a, GLfloat b, GLfloat c, glm::vec3 Center, GLint d, BodyPart h, GLuint k);
	void drawBodyPart();
	void addBodyPart(BodyParts *part, glm::vec3 Offset);
	// void startWalking(GLint noSteps);
	void swingHand(GLint a)
	{
		if (this->type == LeftHand || this->type == RightHand || this->type == LeftLeg || this->type == RightLeg)
		{
			if (a == 1)
			{
				if (this->angle0 <= 145.0f)
					this->angle0 += 5.0f;
			}
			else if (a == 2)
			{
				if (this->angle0 > 0.0f)
					this->angle0 -= 5.0f;
			}
			// std::cout << glm::to_string(this->point_Inflne1) << "\n";
		}
		// else if (this->type == RightHand)
		// {
		// 	if (a == 1)
		// 	{
		// 		if (this->angle0 <= 145.0f) this->angle0 += 5.0f;
		// 	}
		// 	else if (a == 2)
		// 	{
		// 		if (this->angle0 > 0.0f) this->angle0 -= 5.0f;
		// 	}
		// }
		// else if (this->type == LeftLeg)
		// {
		// 	if (a == 1)
		// 	{
		// 		if (this->angle0 <= 145.0f) this->angle0 += 5.0f;
		// 	}
		// 	else if (a == 2)
		// 	{
		// 		if (this->angle0 > 0.0f) this->angle0 -= 5.0f;
		// 	}
		// }
		else if (this->type == LeftArm)
		{
			if (a == 1)
			{
				if (this->angle1 < 65.0f)
					this->angle1 += 5.0f;
				// else if (this->angle1 < 0.0f) this->angle1 = 0.0f;
			}
			else if (a == 2)
			{
				if (this->angle2 < 65.0f)
					this->angle2 += 5.0f;
				// else if (this->angle2 < 0.0f) this->angle2 = 0.0f;
				// std::cout << this->angle2 << "\n";
			}
			else if (a == 3)
			{
				if (this->angle1 > -65.0f)
					this->angle1 -= 5.0f;
				// else if (this->angle2 < 0.0f) this->angle2 = 0.0f;
				// std::cout << this->angle2 << "\n";
			}
			else if (a == 4)
			{
				if (this->angle2 > -65.0f)
					this->angle2 -= 5.0f;
				// else if (this->angle2 < 0.0f) this->angle2 = 0.0f;
				// std::cout << this->angle2 << "\n";
			}
			for (std::vector<std::pair<BodyParts *, glm::vec3>>::iterator it = this->children.begin(); it != this->children.end(); ++it)
			{
				BodyParts *temp = it->first;
				// glm::mat4 model = glm::mat4(1.0f);
				// model = glm::translate(model, this->center);
				// model = glm::translate(model, this->point_Inflne1);
				// model = glm::rotate(model, glm::radians(-this->angle1),glm::normalize(this->point_Inflne1 - this->point_Inflne2));
				// model = glm::rotate(model, glm::radians(-this->angle2),glm::cross((this->center - this->point_Inflne1), (this->point_Inflne2 - this->point_Inflne1)));
				// model = glm::translate(model, -this->point_Inflne1);
				// model = glm::translate(model, temp->center1);
				// temp->center = glm::vec3(model*glm::vec4(temp->center1, 0.0f));
				// temp->point_Inflne1 = glm::normalize(glm::vec3(model*glm::vec4(temp->point_Inflne3, 0.0f)));
				// temp->point_Inflne2 = glm::normalize(glm::vec3(model*glm::vec4(temp->point_Inflne4, 0.0f)));
				temp->angle1 = this->angle1;
				temp->angle2 = this->angle2;
				temp->point_Inflne1 = this->point_Inflne1;
				temp->point_Inflne2 = this->point_Inflne2;
				// std::cout << glm::to_string(glm::vec3(model*glm::vec4(temp->center1, 0.0f))) << "\n";
				// std::cout << glm::to_string(temp->center1) << "\n";
				// std::cout << glm::distance(glm::vec3(model*glm::vec4(temp->center1, 0.0f)), glm::vec3(model*glm::vec4(this->center, 0.0f))) << "\n";
				// if (temp->angle <= 145.0f) temp->angle+=5.0f;
				// else if (temp->angle < 0.0f) temp->angle = 0.0f;
			}
		}
		else if (this->type == RightArm)
		{
			if (a == 1)
			{
				if (this->angle1 < 65.0f)
					this->angle1 += 5.0f;
				// else if (this->angle1 < 0.0f) this->angle1 = 0.0f;
			}
			else if (a == 2)
			{
				if (this->angle2 < 65.0f)
					this->angle2 += 5.0f;
				// else if (this->angle2 < 0.0f) this->angle2 = 0.0f;
				// std::cout << this->angle2 << "\n";
			}
			else if (a == 3)
			{
				if (this->angle1 > -65.0f)
					this->angle1 -= 5.0f;
				// else if (this->angle2 < 0.0f) this->angle2 = 0.0f;
				// std::cout << this->angle2 << "\n";
			}
			else if (a == 4)
			{
				if (this->angle2 > -65.0f)
					this->angle2 -= 5.0f;
				// else if (this->angle2 < 0.0f) this->angle2 = 0.0f;
				// std::cout << this->angle2 << "\n";
			}
			for (std::vector<std::pair<BodyParts *, glm::vec3>>::iterator it = this->children.begin(); it != this->children.end(); ++it)
			{
				BodyParts *temp = it->first;
				// glm::mat4 model = glm::mat4(1.0f);
				// model = glm::translate(model, this->center);
				// model = glm::translate(model, this->point_Inflne1);
				// model = glm::rotate(model, glm::radians(-this->angle1),glm::normalize(this->point_Inflne1 - this->point_Inflne2));
				// model = glm::rotate(model, glm::radians(-this->angle2),glm::cross((this->center - this->point_Inflne1), (this->point_Inflne2 - this->point_Inflne1)));
				// model = glm::translate(model, -this->point_Inflne1);
				// model = glm::translate(model, temp->center1);
				// temp->center = glm::vec3(model*glm::vec4(temp->center1, 0.0f));
				// temp->point_Inflne1 = glm::normalize(glm::vec3(model*glm::vec4(temp->point_Inflne3, 0.0f)));
				// temp->point_Inflne2 = glm::normalize(glm::vec3(model*glm::vec4(temp->point_Inflne4, 0.0f)));
				temp->angle1 = this->angle1;
				temp->angle2 = this->angle2;
				temp->point_Inflne1 = this->point_Inflne1;
				temp->point_Inflne2 = this->point_Inflne2;
				// std::cout << glm::to_string(glm::vec3(model*glm::vec4(temp->center1, 0.0f))) << "\n";
				// std::cout << glm::to_string(temp->center1) << "\n";
				// std::cout << glm::distance(glm::vec3(model*glm::vec4(temp->center1, 0.0f)), glm::vec3(model*glm::vec4(this->center, 0.0f))) << "\n";
				// if (temp->angle <= 145.0f) temp->angle+=5.0f;
				// else if (temp->angle < 0.0f) temp->angle = 0.0f;
			}
		}
		else if (this->type == LeftThigh || this->type == RightThigh)
		{
			if (a == 1)
			{
				if (this->angle1 < 65.0f)
					this->angle1 += 5.0f;
				// else if (this->angle1 < 0.0f) this->angle1 = 0.0f;
			}
			else if (a == 2)
			{
				if (this->angle2 < 65.0f)
					this->angle2 += 5.0f;
				// else if (this->angle2 < 0.0f) this->angle2 = 0.0f;
				// std::cout << this->angle2 << "\n";
			}
			else if (a == 3)
			{
				if (this->angle1 > -65.0f)
					this->angle1 -= 5.0f;
				// else if (this->angle2 < 0.0f) this->angle2 = 0.0f;
				// std::cout << this->angle2 << "\n";
			}
			else if (a == 4)
			{
				if (this->angle2 > -65.0f)
					this->angle2 -= 5.0f;
				// else if (this->angle2 < 0.0f) this->angle2 = 0.0f;
				// std::cout << this->angle2 << "\n";
			}
			for (std::vector<std::pair<BodyParts *, glm::vec3>>::iterator it = this->children.begin(); it != this->children.end(); ++it)
			{
				BodyParts *temp = it->first;
				// glm::mat4 model = glm::mat4(1.0f);
				// model = glm::translate(model, this->center);
				// model = glm::translate(model, this->point_Inflne1);
				// model = glm::rotate(model, glm::radians(-this->angle1),glm::normalize(this->point_Inflne1 - this->point_Inflne2));
				// model = glm::rotate(model, glm::radians(-this->angle2),glm::cross((this->center - this->point_Inflne1), (this->point_Inflne2 - this->point_Inflne1)));
				// model = glm::translate(model, -this->point_Inflne1);
				// model = glm::translate(model, temp->center1);
				// temp->center = glm::vec3(model*glm::vec4(temp->center1, 0.0f));
				// temp->point_Inflne1 = glm::normalize(glm::vec3(model*glm::vec4(temp->point_Inflne3, 0.0f)));
				// temp->point_Inflne2 = glm::normalize(glm::vec3(model*glm::vec4(temp->point_Inflne4, 0.0f)));
				temp->angle1 = this->angle1;
				temp->angle2 = this->angle2;
				temp->point_Inflne1 = this->point_Inflne1;
				temp->point_Inflne2 = this->point_Inflne2;
				// std::cout << glm::to_string(glm::vec3(model*glm::vec4(temp->center1, 0.0f))) << "\n";
				// std::cout << glm::to_string(temp->center1) << "\n";
				// std::cout << glm::distance(glm::vec3(model*glm::vec4(temp->center1, 0.0f)), glm::vec3(model*glm::vec4(this->center, 0.0f))) << "\n";
				// if (temp->angle <= 145.0f) temp->angle+=5.0f;
				// else if (temp->angle < 0.0f) temp->angle = 0.0f;
			}
		}
	}
};

/**
 * Graphical human body
 **/
class Humanoid
{
	/**
	 * gender
	 */
	char gender;

public:
	// root is chest
	BodyParts *root;

	GLfloat count = 0.0f;
	GLint isDone = 0;

	GLboolean isShift = GL_FALSE;

	Humanoid(glm::vec3 center, GLint ShaderProgram, char gender);
	
	/**
	 * adds body parts
	 */
	void addBodyPart(BodyParts *part, glm::vec3 Offset);
	
	/**
	 * Displays the human
	 */
	void visible();
	void rotCen()
	{
		root->cen += 5.0f;
	}
	// void startWalking(GLint noSteps);
	~Humanoid();
};