#include "CharList.h"

CharList::CharList(float zn, float zf, float ap, float fy)
	:size(1.0f), znear(zn), zfar(zf), aspect(ap), fovy(fy){
	//�ַ������ַ�����
	num = 15 + rand() % 10;
	RndPos();//���λ��
	glm::vec3 tp = pos;
	float alpha = 1.0f;
	for (auto x = 0; x < num; ++x) {//����num���ַ�
		Symbol tmp;
		tmp.Color = glm::vec4(0.0, 1.0, 0.5, alpha);
		tmp.Pos = glm::vec4(tp.x, tp.y, tp.z, size);
		//�������
		tmp.Coord.x = rand() % 11;
		tmp.Coord.y = rand() % 6;
		necklace.push_back(tmp);
		tp.y += size;
		alpha -= 1.0f / num;
	}
	//ͷ������ɫΪ��ɫ
	necklace.front().Color = glm::vec4(0.8, 0.8, 0.8, 1.0);
	//�ٶ�
	vel = glm::vec3(0.0, -0.1, 0.022);
}

void CharList::Move(float dt) {
	//ͷ�����룬ɾ��β��
	Symbol tmp;
	tmp.Color = glm::vec4(0.8, 0.8, 0.8, 1.0);
	tmp.Pos = glm::vec4(necklace.front().Pos.x, necklace.front().Pos.y, necklace.front().Pos.z, size);
	tmp.Pos.y -= size;
	tmp.Coord.x = rand() % 11;
	tmp.Coord.y = rand() % 6;
	necklace.front().Color = glm::vec4(0.0, 1.0, 0.5, 1.0f);
	necklace.push_front(tmp);
	necklace.pop_back();
	//�޸�alphaֵ
	float alpha = 1.0f;
	for (auto &e : necklace) {
		e.Color.w = alpha;
		alpha -= 1.0f / num;
		e.Pos.z += vel.z;
		//e.Pos.w = size * 2;
	}
	pos = necklace.front().Pos;
}

bool CharList::IsOufScreen() {
	//�ж��Ƿ�Ʈ����Ļ
	double range = tan(glm::radians(fovy))*pos.z;
	float length = num * size;
	if (pos.z >= -znear || pos.z <= -this->zfar || pos.y < (range - length)){
		return true;
	}
	return false;
}

void CharList::RndPos() {
	//���λ������
	double range;
	pos.z = -(Rand0_1()*(zfar - znear) + znear);
	range = tan(glm::radians(fovy))*pos.z;
	pos.y = -range;
	pos.x = Rand0_1()*range * 2 * aspect - range*aspect;
}
 