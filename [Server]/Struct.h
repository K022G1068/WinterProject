struct Matrix3x3 {
	float m[3][3];
};

struct Matrix2x2 {
	float m[2][2];
};
struct Vector2 {
	float x, y;
};

struct Hp {
	float barPercentage;
	float playerHp;
	float maxHp;
	float saveHp;
};

struct Square {
	Vector2 topLeft;
	Vector2 bottomLeft;
	Vector2 topRight;
	Vector2 bottomRight;
};

struct ShakeElement
{
	Vector2 shakePos;
	bool IsShaking;
	int shakeTime;
};

struct Bullet
{
	int bulletRange;
	int bulletSpeed;
	int bulletDamage;
	int w_Damage;
	int w_Speed;
	Vector2 w_Pos;
	Vector2 w_Base_Pos;
	bool isShooting[2] = { false,false };
};

enum face
{
	LEFT,
	RIGHT,
};

