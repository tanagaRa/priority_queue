#pragma once
#include <cassert>
#include <iostream>
#include <vector>

/*в задание требуется тип int, поэтому не использованы шаблоны*/

class PriorityQueue {
 public:
  struct Node;
  enum class Priority {
    high = 1,
    medium = 2,
    low = 3
  };

 public:
  PriorityQueue() = default;           //конструктор по умолчанию
  PriorityQueue(const PriorityQueue& queue);        //конструктор копирования
  PriorityQueue(PriorityQueue&& queue) noexcept;         //конструктор перемещения
  PriorityQueue& operator=(const PriorityQueue& queue);     //копирующий оператор присваивания
  PriorityQueue& operator=(PriorityQueue&& queue) noexcept; //перемещающий оператор присваивания
  ~PriorityQueue();                     //деструктор

 public:
  [[nodiscard]] int Size() const;      //возврат длину
  int GetValueOfHead() const;      //возврат значения головного элемента
  Priority GetPriorityOfHead() const;   //возврат приоритета головного элемента
  [[nodiscard]] int GetCountOfHighPriority() const; //количество элементов высшего приоритета
  [[nodiscard]] int GetCountOfMediumPriority() const;//количество элементов средней важности
  [[nodiscard]] int GetCountOfLowPriority() const;//количество элементов низшей важности
  [[nodiscard]] bool IsEmpty() const;  //проверка на пустоту
  void Push(const int& value, Priority priority);  //добавление элементов путём копировния
  void Push(int&& value, Priority priority); //добавление элементов путём перемещения
  void Pop(); //удаление элемента
  void Clear(); //очищение всей очереди

 private:
  Node* head_{nullptr};
  size_t size_{0};            //вектор длины очереди
  int count_of_high_priority{0};  //вектор для высших...
  int count_of_medium_priority{0}; //...средних...
  int count_of_low_priority{0};   //...низших элементов
};