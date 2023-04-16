
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "AnimatedFrame.h"
#include "Position.h"
#include "Quaternion.h"
#include "AnimatedTransform.h"
#include <string>
#include <iostream>
#include "main.h"
using namespace std;


int main()
{
	printf("Enter Location to your animation file of sf3 beta version \n");
	std::string path = "";
	std::cin >> path;
	FILE* infile = fopen(path.c_str(), "rb");
	long long header = 0;
	fread(&header, 1, sizeof(long long), infile);
	if (header != 457546134634732L)
	{
		printf("Wrong animation file type");
		return 0;
	}
	int16_t garbageBufferSize = 0;
	fread(&garbageBufferSize, 1, sizeof(int16_t), infile);

	long long* garbage = (long long*)malloc(sizeof(long long) * garbageBufferSize);

	for (int i = 0; i < garbageBufferSize; i++)
	{
		fread(&garbage[i], 1, sizeof(long long), infile);
	}
	int framesLength = 0;
	fread(&framesLength, 1, sizeof(int), infile);
	printf("\nTotal Number of frames in this animation are %d", framesLength);

	AnimatedFrame* frames = (AnimatedFrame*)malloc(sizeof(AnimatedFrame) * framesLength);

	int boneIDsLength = 0;
	fread(&boneIDsLength, 1, sizeof(int), infile);
	printf("\n Total Number of bones used in this animation are %d", boneIDsLength);

	int16_t* boneIDs = (int16_t*)malloc(sizeof(int16_t) * boneIDsLength);
	for (int i = 0; i < boneIDsLength; i++)
	{
		fread(&boneIDs[i], 1, sizeof(int16_t), infile);
	}
	printf("\n Here are the bonesIDS:-");
	for (int i = 0; i < boneIDsLength; i++)
	{
		if (boneIDs[i] < 61)
		{
			Bones bone = (Bones)boneIDs[i];
			printf("\n    BoneID[ %d ] = %u  =   ", i, boneIDs[i]);
			cout << getEnumValue(bone);
		}
	}

	printf("\n \n Here are the BoneIDS and their position and rotations:-");


	float* array = (float*)malloc(sizeof(float) * framesLength * boneIDsLength * 7);
	int arrayLength = framesLength * boneIDsLength * 7;

	for (int i = 0; i < arrayLength; i++)
	{
		fread(&array[i], 1, sizeof(float), infile);
	}
	for (int i = 0; i < framesLength; i++)
	{
		printf("\nFrame{ %d } :-", i);
		frames[i] = *(AnimatedFrame *)malloc(sizeof(AnimatedFrame));
		frames[i].bonesAnimation = (AnimatedTransform*)malloc(sizeof(AnimatedTransform) * boneIDsLength);
		for (int j = 0; j < boneIDsLength; j++)
		{
			printf("\n     BoneID { %hd } :-", boneIDs[j]);
			int num = j * 7 + i * 7;
			Position position = *(Position*)malloc(sizeof(position));
			position.p1 = array[num];
			position.p2 = array[num + 1];
			position.p3 = array[num + 2];
			printf("\n             Position { %f , %f , %f } ", position.p1, position.p2, position.p3);
			Quaternion quaternion = *(Quaternion*)malloc(sizeof(Quaternion));
			quaternion.q1 = array[num + 3];
			quaternion.q2 = array[num + 4];
			quaternion.q3 = array[num + 5];
			quaternion.q4 = array[num + 6];
			printf("\n             Rotation { %f , %f , %f , %f } ", quaternion.q1, quaternion.q2, quaternion.q3, quaternion.q4);
			frames[i].bonesAnimation[j] = AnimatedTransform::AnimatedTransform(position, quaternion);
		}
	}
	printf("\n");
	system("pause");
	return 1;
}
