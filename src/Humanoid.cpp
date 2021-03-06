#include "include/Humanoid.h"


GLuint LoadTexture( const char * filename, GLboolean alpha = GL_FALSE);

void BodyParts::drawBodyPart()
{
	// matter = new Atom();
	// matter->center = this->center;

	glBindVertexArray(this->matter->VAO);
	// std::cout << glm::to_string(this->point_Inflne1) << "\n";
	// std::cout << this->angle1 << "\n";
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, this->shift);
	model = glm::translate(model, this->pCentroid);
	model = glm::rotate(model, glm::radians(this->cen), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, -this->pCentroid);
	model = glm::translate(model, this->point_Inflne1);
	model = glm::rotate(model, glm::radians(-this->angle1), glm::normalize(this->point_Inflne1 - this->point_Inflne2));
	model = glm::rotate(model, glm::radians(-this->angle2), glm::cross((this->center - this->point_Inflne1), (this->point_Inflne2 - this->point_Inflne1)));
	model = glm::translate(model, -this->point_Inflne1);
	model = glm::translate(model, this->center);
	// if (this->type == LeftHand)
	// {
	model = glm::translate(model, this->point_Inflne3);
	if (this->type != RightHand && this->type != LeftLeg && this->type != RightLeg)
		model = glm::rotate(model, glm::radians(this->angle0), glm::cross((this->center - this->point_Inflne1), (this->point_Inflne2 - this->point_Inflne1)));
	else
		model = glm::rotate(model, glm::radians(-this->angle0), glm::cross((this->center - this->point_Inflne1), (this->point_Inflne2 - this->point_Inflne1)));

	model = glm::translate(model, -this->point_Inflne3);
	// std::cout << glm::to_string(this->pCentroid) << "\n";
	// std::cout << glm::to_string(glm::vec3(model * glm::vec4(this->center,0.0f))) << "\n";
	// std::cout << glm::to_string(this->point_Inflne1) << "\n";
	// }
	// if (this->type == LeftArm)
	// {
	// model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
	// model = glm::rotate(model, glm::radians(-this->angle), glm::vec3(0.0f, 0.0f, 1.0f));
	// model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
	// glm::vec4 temp = glm::vec4(model * glm::vec4(this->center,0.0f));
	// this->center = glm::vec3(temp);
	// std::cout<<glm::to_string(temp)<<std::endl;
	// }
	model = glm::scale(model, glm::vec3(length, height, breadth));
	GLuint transformLoc1 = glGetUniformLocation(this->ShaderProgram, "model");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
	glBindTexture(GL_TEXTURE_2D, this->texture);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);

	for (std::vector<std::pair<BodyParts *, glm::vec3>>::iterator it = this->children.begin(); it != this->children.end(); ++it)
	{
		BodyParts *temp = it->first;
		// temp->matter = new Atom();
		// temp->center = it->second + this->center;
		// temp->point_Inflne1 = temp->center + glm::vec3(temp->length / 2.0, 0.0, 0.0f);
		// temp->point_Inflne2 = temp->center + glm::vec3(temp->length / 2.0, temp->height/ 2.0, 0.0f);
		// std::cout << glm::to_string(temp->point_Inflne) << "\n";
		temp->pCentroid = this->pCentroid;
		temp->cen = this->cen;
		temp->shift = this->shift;
		if (this->type != Torso)
		{
			temp->angle1 = this->angle1;
			temp->angle2 = this->angle2;
			temp->point_Inflne1 = this->point_Inflne1;
			temp->point_Inflne2 = this->point_Inflne2;
		}
		if (this->type == Head)
		{
			temp->center = it->second + this->center;
		}
		temp->drawBodyPart();
		// std::cout << temp->length << "\t" << temp->breadth << "\t" << temp->height << "\n";
		// // std::cout << temp->ShaderProgram << "\n";
		// glBindVertexArray(temp->matter->VAO);
		// glm::mat4 model = glm::mat4(1.0f);
		// model = glm::translate(model, temp->matter->center);
		// model = glm::scale(model, glm::vec3(temp->length, temp->height, temp->breadth));
		// GLuint transformLoc1 = glGetUniformLocation(temp->ShaderProgram, "model");
		// glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(model));
		// glDrawArrays(GL_TRIANGLES, 0, 36);
		// glBindVertexArray(0);
	}
	// std::cout << "ello\n";
}

BodyParts::BodyParts(GLfloat a, GLfloat b, GLfloat c, glm::vec3 Center, GLint d, BodyPart h, GLuint k)
{
	length = a;
	breadth = b;
	height = c;
	center = Center;
	center1 = Center;
	ShaderProgram = d;
	type = h;
	texture = k;
	matter = new Atom();
	if (h == LeftArm || h == LeftHand)
	{
		point_Inflne1 = Center + glm::vec3(a / 2.0, 0.0f, 0.0f);
		point_Inflne2 = Center + glm::vec3(a / 2.0, c / 2.0, 0.0f);
		point_Inflne3 = Center + glm::vec3(a / 2.0, 0.0f, 0.0f);
		point_Inflne4 = Center + glm::vec3(a / 2.0, c / 2.0, 0.0f);
	}
	else if (h == RightArm || h == RightHand)
	{
		point_Inflne1 = Center - glm::vec3(a / 2.0, 0.0f, 0.0f);
		point_Inflne2 = Center - glm::vec3(a / 2.0, c / 2.0, 0.0f);
		point_Inflne3 = Center - glm::vec3(a / 2.0, 0.0f, 0.0f);
		point_Inflne4 = Center - glm::vec3(a / 2.0, c / 2.0, 0.0f);
	}
	else if (h == LeftThigh || h == LeftLeg)
	{
		point_Inflne1 = Center + glm::vec3(0.0f, c / 2.0, 0.0f);
		point_Inflne2 = Center + glm::vec3(0.0f, c / 2.0, b / 2.0);
		point_Inflne3 = Center + glm::vec3(0.0f, c / 2.0, 0.0f);
		point_Inflne4 = Center + glm::vec3(0.0f, c / 2.0, b / 2.0);
	}
	else if (h == RightThigh || h == RightLeg)
	{
		point_Inflne1 = Center + glm::vec3(0.0f, c / 2.0, 0.0f);
		point_Inflne2 = Center + glm::vec3(0.0f, c / 2.0, b / 2.0);
		point_Inflne3 = Center + glm::vec3(0.0f, c / 2.0, 0.0f);
		point_Inflne4 = Center + glm::vec3(0.0f, c / 2.0, b / 2.0);
	}
	else
	{
		point_Inflne1 = Center + glm::vec3(a / 2.0, 0.0f, 0.0f);
		point_Inflne2 = Center + glm::vec3(a / 2.0, c / 2.0, 0.0f);
		point_Inflne3 = Center + glm::vec3(a / 2.0, 0.0f, 0.0f);
		point_Inflne4 = Center + glm::vec3(a / 2.0, c / 2.0, 0.0f);
	}
	// std::cout << glm::to_string(point_Inflne2) << "\n";
}

void BodyParts::addBodyPart(BodyParts *part, glm::vec3 Offset)
{
	this->children.push_back(std::make_pair(part, Offset));
	part->center = Offset + this->center;
	part->center1 = Offset + this->center;
}

// void BodyParts::startWalking(GLint noSteps)
// {
// 	this->position += noSteps;
// 	for (std::vector<std::pair<BodyParts*, glm::vec3>>::iterator it = this->children.begin() ; it != this->children.end(); ++it)
// 	{
// 		BodyParts* temp = it->first;
// 		temp->position += noSteps;
// 		temp->startWalking(noSteps);
// 	}
// }

Humanoid::Humanoid(glm::vec3 Center, GLint shaderProgram, char gender)
{
	// stomach
	root = new BodyParts(1.0f, 0.75f, 1.5f, Center, shaderProgram, Torso, -1);
	root->pCentroid = Center;
	this->gender = gender;
	// BodyPart k = Torso;
	// root->type = k;

	GLuint texture3 = LoadTexture("textures/boyf1.jpg");
	GLuint texture4 = LoadTexture("textures/boyfb.jpg");
	GLuint neckTex = LoadTexture("textures/neck.jpg");
	GLuint shirtTex = LoadTexture("textures/shirt.jpg");
	GLuint pantTex = LoadTexture("textures/pant.jpg");
	GLuint weddingTex = LoadTexture("textures/wedding4.jpg");
	GLuint texture5 = LoadTexture("textures/girlf1.jpg");
	GLuint texture6 = LoadTexture("textures/girlfb.jpg");

	root->texture = gender == 'M' ? shirtTex : weddingTex;

	BodyParts *neck = new BodyParts(0.25f, 0.3f, 0.25f, root->center1 + glm::vec3(0.0f, (root->height / 2.0) + 0.1f, 0.0f), 
						shaderProgram, Neck, neckTex);
	BodyParts *head =  new BodyParts(0.5f, 0.55f, 0.5f,   glm::vec3(0.0f), shaderProgram, Head, -1);
	BodyParts *headf = new BodyParts(0.5f, 0.005f, 0.5f,  glm::vec3(0.0f), shaderProgram, Plate, gender == 'M' ? texture3 : texture5);
	BodyParts *headb = new BodyParts(0.5f, 0.005f, 0.5f,  glm::vec3(0.0f), shaderProgram, Plate, gender == 'M' ? texture4 : texture6);
	BodyParts *headl = new BodyParts(0.01f, 0.55f, 0.5f,  glm::vec3(0.0f), shaderProgram, Plate, gender == 'M' ? texture4 : texture6);
	BodyParts *headr = new BodyParts(0.01f, 0.55f, 0.5f,  glm::vec3(0.0f), shaderProgram, Plate, gender == 'M' ? texture4 : texture6);
	BodyParts *headt = new BodyParts(0.5f, 0.55f, 0.005f, glm::vec3(0.0f), shaderProgram, Plate, gender == 'M' ? texture4 : texture6);
	head->addBodyPart(headf, glm::vec3(0.0f, 0.0f, head->breadth / 2.0f - 0.001f));
	head->addBodyPart(headb, glm::vec3(0.0f, 0.0f, -(head->breadth / 2.0f + 0.001f)));
	head->addBodyPart(headl, glm::vec3(-(head->length / 2.0f + 0.001f), 0.0f, 0.0f));
	head->addBodyPart(headr, glm::vec3((head->length / 2.0f + 0.001f), 0.0f, 0.0f));
	head->addBodyPart(headt, glm::vec3(0.0f, (head->height / 2.0f + 0.001f), 0.0f));
	neck->addBodyPart(head, glm::vec3(0.0f, 0.4f, 0.0f));
	addBodyPart(neck, glm::vec3(0.0f));

	BodyParts *lArm = new BodyParts(0.75f, 0.25f, 0.25f, root->center1 + glm::vec3(-root->length, root->breadth-0.2f, 0.0f), shaderProgram, 
						LeftArm, gender == 'M' ? shirtTex : neckTex);
	BodyParts *lHand = new BodyParts(0.8f, 0.2f, 0.2f, glm::vec3(0.0f), shaderProgram, LeftHand, neckTex);
	lArm->addBodyPart(lHand, glm::vec3(-0.8f, 0.0f, 0.0f));
	addBodyPart(lArm, glm::vec3(0.0f));

	BodyParts *rArm = new BodyParts(0.75f, 0.25f, 0.25f, root->center1 + glm::vec3(root->length, root->breadth-0.2f, 0.0f), shaderProgram, 
						RightArm, gender == 'M' ? shirtTex : neckTex);
	BodyParts *rHand = new BodyParts(0.8f, 0.2f, 0.2f, glm::vec3(0.0f), shaderProgram, RightHand, neckTex);
	rArm->addBodyPart(rHand, glm::vec3(0.8f, 0.0f, 0.0f));
	addBodyPart(rArm, glm::vec3(0.0f));

	BodyParts *lThigh = new BodyParts(0.35f, 0.45f, 0.85f, root->center1 + glm::vec3(-0.25f, -root->height+0.3f, 0.0f), shaderProgram, 
						LeftThigh, gender == 'M' ? pantTex : weddingTex);
	BodyParts *lLeg = new BodyParts(0.25f, 0.25f, 0.9f, glm::vec3(0.0f), shaderProgram, LeftLeg, gender == 'M' ? pantTex : neckTex);
	lThigh->addBodyPart(lLeg, glm::vec3(0.0f, -0.8f, 0.0f));
	addBodyPart(lThigh, glm::vec3(0.0f));

	BodyParts *rThigh = new BodyParts(0.35f, 0.45f, 0.85f, root->center1 + glm::vec3(0.25f, -root->height+0.3f, 0.0f), shaderProgram, 
						RightThigh, gender == 'M' ? pantTex : weddingTex);
	BodyParts *rLeg = new BodyParts(0.25f, 0.25f, 0.9f, glm::vec3(0.0f), shaderProgram, RightLeg, gender == 'M' ? pantTex : neckTex);
	rThigh->addBodyPart(rLeg, glm::vec3(0.0f, -0.8f, 0.0f));
	addBodyPart(rThigh, glm::vec3(0.0f));

	// animation
	for (int i = 0; i < 5; ++i)
	{
		lHand->swingHand(1);
		lArm->swingHand(1);
		rArm->swingHand(1);
		rArm->swingHand(4);
	}
	for (int i = 0; i < 3; ++i)
	{
		lArm->swingHand(4);
		lArm->swingHand(1);
		rHand->swingHand(1);
	}
	rHand->swingHand(1);
}

void Humanoid::addBodyPart(BodyParts *part, glm::vec3 Offset)
{
	root->children.push_back(std::make_pair(part, Offset));
	part->pCentroid = root->center1;
}

void Humanoid::visible()
{
	if (isShift)
	{
		if (count < 135.0f)
			count += 0.5f;
		if (count == 135.0f && isDone == 0)
		{
			isDone = 1;
		}
	}
	else
	{
		if (count > 0)
			count -= 0.5f;
		if (count == 0.0f && isDone == 1)
		{
			root->cen = 0.0f;
			isDone = 0;
		}
	}
	root->shift = glm::vec3(0.0f, (5.75f * count / 135.0), 0.0f);
	root->drawBodyPart();
}

// void Humanoid::startWalking(GLint noSteps)
// {
// 	//root->startWalking(noSteps);
// 	root->center += glm::vec3(0.0f, 0.0f, noSteps);
// }

Humanoid::~Humanoid()
{
}
