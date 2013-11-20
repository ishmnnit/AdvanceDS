class MinFibnode
 {
  public:
  int degree;
  int data;
  int fvertexid;
  int weight;
  MinFibnode* child;
  MinFibnode* parent;
  MinFibnode* left;
  MinFibnode* right;
  bool childcut;

};

class MinFibheap
{
  MinFibnode* root;
  int nodecount;

  public:

  MinFibheap();
  void insert(MinFibnode*);
  MinFibnode* remove_min();
  void decrease_key(MinFibnode*,int);
  void pairwise_combine();
  void pairwise_combine1();
  void cascade_cut(MinFibnode*);
  void cut(MinFibnode*,MinFibnode*);
  void fibonacci_link(MinFibnode*,MinFibnode*);
  MinFibnode* make_fibnode(int,int,int);
 };
