#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

struct Coord {
  int x;
  int y;

  inline bool operator==(const Coord& classRef) {
    return ((classRef.x == x) && (classRef.y == y));
  }

};

class GameObject
{
  public:
    GameObject();
    virtual ~GameObject();

    void setPosition(Coord pos);

    Coord getPos() const;

  private:
    GameObject(const GameObject& classRef);
    GameObject& operator=(const GameObject& classRef);

    Coord pos_;
};

#endif // GAMEOBJECT_HPP