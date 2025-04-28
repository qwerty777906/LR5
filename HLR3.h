#ifndef HLR3_H_INCLUDED
#define HLR3_H_INCLUDED

#include <vector>
#include <list>

using namespace std;

template <typename T>
class Iterator
{
public:
    virtual ~Iterator() {}
    virtual void go_first() = 0;
    virtual void go_next() = 0;
    virtual bool is_done() const = 0;
    virtual T current_item() const = 0;
};

template <typename T>
class IContainer {
public:
    virtual ~IContainer() = default;
    virtual Iterator<T>* GetIterator() = 0;
};

template <typename T>
class VectorWalker : public Iterator<T>
{
private:
    vector<T>* vec;
    size_t index;

public:
    VectorWalker(vector<T>* v) : vec(v), index(0) {}

    void go_first() { index = 0; }
    void go_next() { index++; }
    bool is_done() const { return index >= vec->size(); }
    T current_item() const  { return (*vec)[index]; }
};

template <typename T>
class ListWalker : public Iterator<T>
{
private:
    list<T>* lst;
    typename list<T>::iterator it;

public:
    ListWalker(list<T>* l) : lst(l), it(l->begin()) {}

    void go_first() override { it = lst->begin(); }
    void go_next() override { it++; }
    bool is_done() const override { return it == lst->end(); }
    T current_item() const override { return *it; }
};

template <typename T>
class VectorContainer : public IContainer<T>
{
private:
    vector<T> items;

public:
    void add_item(T&& item) { items.push_back(move(item)); }
    size_t count() const { return items.size(); }
    auto begin() { return VectorWalker<T>(&items); }
    auto end() { return VectorWalker<T>(&items); }

    Iterator<T> *GetIterator()
    {
        return new VectorWalker<T>(&items);
    };
};

template <typename T>
class ListContainer : public IContainer<T>
{
private:
    list<T> items;

public:
    void add_item(T&& item) { items.push_back(move(item)); }
    size_t count() const { return items.size(); }
    auto begin() { return ListWalker<T>(&items); }
    auto end() { return ListWalker<T>(&items); }

    Iterator<T> *GetIterator()
    {
        return new ListWalker<T>(&items);
    };
};

template<typename T>
class IteratorDecorator : public Iterator<T>
{
protected:
    Iterator<T> *It;

public:
    IteratorDecorator(Iterator<T>* it) : It(it) {}
    virtual ~IteratorDecorator() { delete It; }

    virtual  void go_first() { It->go_first(); }
    virtual  void go_next() { It->go_next(); }
    virtual  bool is_done() const { return It->is_done(); }
    virtual T current_item() const { return It->current_item(); }
};

template<typename ContainerType, typename ItemType>
class ConstIteratorAdapter : public Iterator<ItemType>
{
protected:
    ContainerType *Container;
    typename ContainerType::const_iterator It;

public:
    ConstIteratorAdapter(ContainerType *container)
        : Container(container) {It=container->begin();}

    virtual ~ConstIteratorAdapter() {}
    virtual void go_first() { It = Container->begin(); }
    virtual void go_next() { It++; }
    virtual bool is_done() const { return (It == Container->end()); }
    virtual ItemType current_item() const { return *It; }
};

#endif // HLR3_H_INCLUDED
