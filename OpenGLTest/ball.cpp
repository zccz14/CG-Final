#include "ball.h"
#include "tree_stone.h"

	Vector3 Position;
	Vector3 Velocity;
	real GravitationalA;
	Vector3 FrictionA;
	const real InverseMass = 1.0;
	const real Radius = 0.5;
	Ball Ball1;

	Ball::Ball() {
		Position.x = Position.y = 5.0;
		Position.z = 0.5;
		Velocity.x = Velocity.y = 5.0;
		Velocity.y = 0.0;
		FrictionA.x = FrictionA.y = 0.0;
		GravitationalA = 2.0;
		Radius;
	}


	Ball::Ball(Vector3 BPosition, Vector3 BVelocity) {
		Position.x = BPosition.x;
		Position.y = BPosition.y;
		Position.z = BPosition.z;
		Velocity.x = BVelocity.x;
		Velocity.y = BVelocity.y;
		Velocity.z = BVelocity.z;
	}


	Ball::~Ball() {

	}


	int Chunk::intChunkGet(Vector3 Position) {
		int intChunk = int(Position.x / 10 + 1) * 10 + int(Position.y / 10) + 1;
		return intChunk;
	}//地图设计根据区块确定地形，确定区块可节省大量碰撞检测工作


	 //球-树碰撞检测
	bool Ball::IscollisionT(Vector2 TPosition, Vector3 Position, real TSize) {
		Vector2 xyPosition;
		xyPosition.x = Position.x;
		xyPosition.y = Position.y;
		if (TSize*4.0 + 0.5 <= Position.z ||
			(TSize + 0.5)*(TSize + 0.5) < Vector2::distance22(xyPosition, TPosition))
			return 0;
		else
			return 1;
	}//将树木抽象成圆柱体


	 //球-石头碰撞检测
	bool Ball::IscollisionS(Vector3 TPosition, Vector3 Position, real SSize) {
		if (SSize + 0.5 < Vector3::distance32(Position, TPosition))
			return 0;
		else
			return 1;
	}//将石块抽象成半球体


	 //球-墙碰撞检测
	bool Ball::IscollisionWall(Vector3 Position) {
		if (Position.x <= 0.5 || Position.x >= 99.5 ||
			Position.y <= 0.5 || Position.y >= 99.5)
			return 1;
	}


	//球-水面碰撞检测
	bool Ball::IscollisionWater(Vector3 Position) {
		if (Position.z <= 0.5)
			return 1;
		else
			return 0;
	}


	//球-地面碰撞检测
	int Ball::collisionGround(Vector3 Position, Vector3 Velocity) {
		if (Position.z <= 0.5&&Velocity.z < 0)
			return 1;      //与地面碰撞
		else if (Position.z <= 0.5&&Velocity.z == 0)
			return -1;     //在地面上滚动
		else
			return 0;      //在空中
	}


	//球-树碰撞更新
	Vector3 Ball::colTVelocity(Vector2 TPosition, Vector3 Position, real TSize, Vector3 Velocity) {

		Vector2 xyPosition, xyVelocity;
		xyPosition.x = Position.x;
		xyPosition.y = Position.y;
		xyVelocity.x = Velocity.x;
		xyVelocity.y = Velocity.y;

		Vector3 newVelocity;

		if (TSize*TSize >= Vector2::distance22(xyPosition, TPosition)) {
			newVelocity.x = Velocity.x;
			newVelocity.y = Velocity.y;
			newVelocity.z = -Velocity.z;
		}//碰撞点在顶面

		else if (Position.z <= TSize*4.0) {
			Vector2 center = Vector2::minusVector2(TPosition, xyPosition);
			Vector2 tangentVelocity = Vector2::decoVector2(xyVelocity, center);
			Vector2 normalVelocity = Vector2::minusVector2(xyVelocity, tangentVelocity);
			newVelocity.x = tangentVelocity.x - normalVelocity.x;
			newVelocity.y = tangentVelocity.y - normalVelocity.y;//碰撞后切向速度不变，法向速度相反
			newVelocity.z = Velocity.z;
		}//碰撞点在侧面

		else {
			newVelocity.x = -Velocity.x;
			newVelocity.y = -Velocity.y;
			newVelocity.z = -Velocity.z;
		}//与边相撞简单处理

		return newVelocity;
	}


	//球-石头碰撞更新
	Vector3 Ball::colSVelocity(Vector3 SPosition, Vector3 Position, Vector3 Velocity) {
		Vector3 newVelocity;
		Vector3 center = Vector3::minusVector3(SPosition, Position);
		Vector3 tangentVelocity = Vector3::decoVector3(Velocity, center);
		Vector3 normalVelocity = Vector3::minusVector3(Velocity, tangentVelocity);
		newVelocity.x = tangentVelocity.x - normalVelocity.x;
		newVelocity.y = tangentVelocity.y - normalVelocity.y;
		newVelocity.z = tangentVelocity.z - normalVelocity.z;//碰撞后切向速度不变，法向速度相反
		return newVelocity;
	}


	//球-墙碰撞更新
	Vector3 Ball::colWVelocity(Vector3 Position, Vector3 Velocity) {
		Vector3 newVelocity;
		if (Position.x <= 0.5 || Position.x >= 99.5) {
			newVelocity.x = -Velocity.x;
			newVelocity.y = Velocity.y;
			newVelocity.z = Velocity.z;
		}
		else if (Position.y <= 0.5 || Position.y >= 99.5) {
			newVelocity.x = Velocity.x;
			newVelocity.y = -Velocity.y;
			newVelocity.z = Velocity.z;
		}
		return newVelocity;
	}//忽略同时触碰两边墙壁的情况


	 //球-地面碰撞更新
	Vector3 Ball::colGVelocity(Vector3 Velocity) {
		Vector3 newVelocity;
		newVelocity.x = Velocity.x;
		newVelocity.y = Velocity.y;
		newVelocity.z = -0.8*Velocity.z;
		return newVelocity;
	}//与水平地面碰撞损失竖直方向速度


	 //球的状态更新
	void Ball::updateBall(Ball Ball1) {
		Vector2 xyVelocity, xyVelocitydir;
		Vector3 dP, dV;
		const real dT = 0.05;
		const real u1 = -0.1;
		const real u2 = -0.5;

		int BChunk = Chunk::intChunkGet(this->Position);


		//水面
		if (BChunk == 34 || BChunk == 35 || BChunk == 44)
		{
			if (Ball::IscollisionWater(this->Position)) {
				Ball::~Ball();
				Ball::Ball();
			}
			else
			{
				this->Acceleration.x = this->Acceleration.y = 0;
				this->Acceleration.z = GRAV;            //加速度更新，下同
				dV = Vector3::kVector3(dT, Acceleration);
				this->Velocity = Vector3::addVector3(dV, this->Velocity);   //速度更新，下同
				dP = Vector3::kVector3(dT, this->Velocity);
				this->Position = Vector3::addVector3(dP, this->Position);   //位置更新，下同
			}
		}
		//草地
		else if (BChunk == 22 || BChunk == 33)
		{
			xyVelocity.x = this->Velocity.x;
			xyVelocity.y = this->Velocity.y;
			xyVelocitydir = Vector2::unitVector2(xyVelocity);
			if (this->collisionGround(this->Position, this->Velocity) == -1) {
				this->FrictionA = Vector2::kVector2(u2, xyVelocitydir);
				this->GravitationalA = 0;
				this->Acceleration = Vector2::addAcceleration(FrictionA, GravitationalA);
			}
			else if (this->collisionGround(this->Position, this->Velocity) == 0)
			{
				this->Acceleration.x = this->Acceleration.y = 0;
				this->Acceleration.z = GRAV;
			}
			else if (this->collisionGround(this->Position, this->Velocity) == 1)
			{
				this->Velocity = this->colGVelocity(this->Velocity);
				if (this->Velocity.z < 0.1) {
					this->Velocity.z = 0.0;
					this->Position.z = 0.5;
					this->FrictionA = Vector2::kVector2(u2, xyVelocitydir);
					this->GravitationalA = 0;
					this->Acceleration = Vector2::addAcceleration(FrictionA, GravitationalA);
				}
				else {
					this->Acceleration.x = this->Acceleration.y = 0;
					this->Acceleration.z = GRAV;
				}
			}
			dV = Vector3::kVector3(dT, Acceleration);
			this->Velocity = Vector3::addVector3(dV, this->Velocity);
			dP = Vector3::kVector3(dT, this->Velocity);
			this->Position = Vector3::addVector3(dP, this->Position);
		}
		//石头区
		else if (BChunk == 12 || BChunk == 24 || BChunk == 31 || BChunk == 41)
		{
			Stone nearStone = Stone::FindStone(BChunk);
			if (this->collisionGround(this->Position, this->Velocity) == -1) {
				if (this->IscollisionS(nearStone.SPosition, this->Position, nearStone.size))
					this->Velocity = this->colSVelocity(nearStone.SPosition, this->Position, this->Velocity);
				this->Acceleration.x = this->Acceleration.y = 0;
				this->Acceleration.z = GRAV;   //与石头碰撞V.z必不为0
			}
			else if (this->collisionGround(this->Position, this->Velocity) == 0)
			{
				if (this->IscollisionS(nearStone.SPosition, this->Position, nearStone.size))
					this->Velocity = this->colSVelocity(nearStone.SPosition, this->Position, this->Velocity);
				this->Acceleration.x = this->Acceleration.y = 0;
				this->Acceleration.z = GRAV;
			}
			else if (this->collisionGround(this->Position, this->Velocity) == 1)
			{
				this->Velocity = this->colGVelocity(this->Velocity);
				if (this->Velocity.z < 0.1) {
					this->Velocity.z = 0.0;
					this->Position.z = 0.5;
					xyVelocity.x = this->Velocity.x;
					xyVelocity.y = this->Velocity.y;
					xyVelocitydir = Vector2::unitVector2(xyVelocity);
					this->FrictionA = Vector2::kVector2(u1, xyVelocitydir);
					this->GravitationalA = 0;
					this->Acceleration = Vector2::addAcceleration(FrictionA, GravitationalA);
				}
				else {
					this->Acceleration.x = this->Acceleration.y = 0;
					this->Acceleration.z = GRAV;
				}
			}
			dV = Vector3::kVector3(dT, Acceleration);
			this->Velocity = Vector3::addVector3(dV, this->Velocity);
			dP = Vector3::kVector3(dT, this->Velocity);
			this->Position = Vector3::addVector3(dP, this->Position);
		}
		//树木区
		else if (BChunk == 32 || BChunk == 43 || BChunk == 54) {
			Tree nearTree = Tree::FindTree(BChunk);
			if (Ball::collisionGround(this->Position, this->Velocity) == -1) {
				if (Ball::IscollisionT(nearTree.TPosition, this->Position, nearTree.size))
					this->Velocity = Ball::colTVelocity(nearTree.TPosition, this->Position, nearTree.size, this->Velocity);
				xyVelocity.x = this->Velocity.x;
				xyVelocity.y = this->Velocity.y;
				xyVelocitydir = Vector2::unitVector2(xyVelocity);
				this->FrictionA = Vector2::kVector2(u1, xyVelocitydir);
				this->GravitationalA = 0;
				this->Acceleration = Vector2::addAcceleration(FrictionA, GravitationalA);
			}
			else if (Ball::collisionGround(this->Position, this->Velocity) == 0)
			{
				if (Ball::IscollisionT(nearTree.TPosition, this->Position, nearTree.size))
					this->Velocity = Ball::colTVelocity(nearTree.TPosition, this->Position, nearTree.size, this->Velocity);
				this->Acceleration.x = this->Acceleration.y = 0;
				this->Acceleration.z = GRAV;
			}
			else if (Ball::collisionGround(this->Position, this->Velocity) == 1)
			{
				this->Velocity = this->colGVelocity(this->Velocity);
				if (this->Velocity.z < 0.1) {
					this->Velocity.z = 0.0;
					this->Position.z = 0.5;
					xyVelocity.x = this->Velocity.x;
					xyVelocity.y = this->Velocity.y;
					xyVelocitydir = Vector2::unitVector2(xyVelocity);
					this->FrictionA = Vector2::kVector2(u1, xyVelocitydir);
					this->GravitationalA = 0;
					this->Acceleration = Vector2::addAcceleration(FrictionA, GravitationalA);
				}
				else {
					this->Acceleration.x = this->Acceleration.y = 0;
					this->Acceleration.z = GRAV;
				}
			}
			dV = Vector3::kVector3(dT, Acceleration);
			this->Velocity = Vector3::addVector3(dV, this->Velocity);
			dP = Vector3::kVector3(dT, this->Velocity);
			this->Position = Vector3::addVector3(dP, this->Position);
		}

		//树木+草地
		else if (BChunk == 23) {
			Tree nearTree = Tree::FindTree(BChunk);
			if (Ball::collisionGround(this->Position, this->Velocity) == -1) {
				if (Ball::IscollisionT(nearTree.TPosition, this->Position, nearTree.size))
					this->Velocity = Ball::colTVelocity(nearTree.TPosition, this->Position, nearTree.size, this->Velocity);
				xyVelocity.x = this->Velocity.x;
				xyVelocity.y = this->Velocity.y;
				xyVelocitydir = Vector2::unitVector2(xyVelocity);
				this->FrictionA = Vector2::kVector2(u2, xyVelocitydir);
				this->GravitationalA = 0;
				this->Acceleration = Vector2::addAcceleration(FrictionA, GravitationalA);
			}
			else if (Ball::collisionGround(this->Position, this->Velocity) == 0)
			{
				if (Ball::IscollisionT(nearTree.TPosition, this->Position, nearTree.size))
					this->Velocity = Ball::colTVelocity(nearTree.TPosition, this->Position, nearTree.size, this->Velocity);
				this->Acceleration.x = this->Acceleration.y = 0;
				this->Acceleration.z = GRAV;
			}
			else if (this->collisionGround(this->Position, this->Velocity) == 1)
			{
				this->Velocity = this->colGVelocity(this->Velocity);
				if (this->Velocity.z < 0.1) {
					this->Velocity.z = 0.0;
					this->Position.z = 0.5;
					xyVelocity.x = this->Velocity.x;
					xyVelocity.y = this->Velocity.y;
					xyVelocitydir = Vector2::unitVector2(xyVelocity);
					this->FrictionA = Vector2::kVector2(u2, xyVelocitydir);
					this->GravitationalA = 0;
					this->Acceleration = Vector2::addAcceleration(FrictionA, GravitationalA);
				}
				else {
					this->Acceleration.x = this->Acceleration.y = 0;
					this->Acceleration.z = GRAV;
				}
			}
			dV = Vector3::kVector3(dT, Acceleration);
			this->Velocity = Vector3::addVector3(dV, this->Velocity);
			dP = Vector3::kVector3(dT, this->Velocity);
			this->Position = Vector3::addVector3(dP, this->Position);
		}

		else {
			xyVelocity.x = this->Velocity.x;
			xyVelocity.y = this->Velocity.y;
			xyVelocitydir = Vector2::unitVector2(xyVelocity);
			if (this->collisionGround(this->Position, this->Velocity) == -1) {
				this->FrictionA = Vector2::kVector2(u1, xyVelocitydir);
				this->GravitationalA = 0;
				this->Acceleration = Vector2::addAcceleration(FrictionA, GravitationalA);
			}
			else if (this->collisionGround(this->Position, this->Velocity) == 0)
			{
				this->Acceleration.x = this->Acceleration.y = 0;
				this->Acceleration.z = GRAV;
			}
			else if (this->collisionGround(this->Position, this->Velocity) == 1)
			{
				this->Velocity = this->colGVelocity(this->Velocity);
				if (this->Velocity.z < 0.1) {
					this->Velocity.z = 0.0;
					this->Position.z = 0.5;
					this->FrictionA = Vector2::kVector2(u1, xyVelocitydir);
					this->GravitationalA = 0;
					this->Acceleration = Vector2::addAcceleration(FrictionA, GravitationalA);
				}
				else {
					this->Acceleration.x = this->Acceleration.y = 0;
					this->Acceleration.z = GRAV;
				}
			}
			dV = Vector3::kVector3(dT, Acceleration);
			this->Velocity = Vector3::addVector3(dV, this->Velocity);
			dP = Vector3::kVector3(dT, this->Velocity);
			this->Position = Vector3::addVector3(dP, this->Position);
		}
	}

