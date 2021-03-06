#include <iostream>
#include <sstream>
#include <string>

template <typename T>
class tree_t
{
private:
    struct node_t
    {
        node_t* left;
        node_t* right;
        T value;
    };

private:
    node_t* root_;

public:
    tree_t()
    {
        root_ = nullptr;
    }
    
    tree_t(std::initializer_list<T> keys){
        root_=nullptr;
        int n = keys.size();
        const int* param = keys.begin();
        for (int i=0; i < n; i++){
            insert(param[i]);
        }
    }
    
    bool isEmpty()
	{
		return (!root_);
	}
    
    bool equal(node_t* a, node_t* b) const{
        if (a==nullptr && b==nullptr) return(true);
        else if (a!=nullptr && b!=nullptr)
        {
            return(
                    a->value == b->value &&
                    equal(a->left, b->left) &&
                    equal(a->right, b->right)
            );
        }
        else return(false);
    }
    
    auto operator==(tree_t const & other) const{
        node_t* a=root_; node_t* b=other.root_;
        return (equal(a, b));
    }

    void insert(T value)
    {
        if (root_ == nullptr)
        {
            root_ = new node_t;
            root_->value = value;
            root_->left = nullptr;
            root_->right = nullptr;
        }
        else
        {
            node_t* run_ = root_;
            while (run_ != nullptr)
            {
                if (value < run_->value)
                {
                    if (run_->left == nullptr)
                    {
                        run_->left = new node_t;
                        run_ = run_->left;
                        run_->value = value;
                        run_->left = nullptr;
                        run_->right = nullptr;
                        return;
                    }
                    else
                    {
                        run_ = run_->left;
                    }
                }
                else if (value >= run_->value)
                {
                    if (run_->right == nullptr)
                    {
                        run_->right = new node_t;
                        run_ = run_->right;
                        run_->value = value;
                        run_->left = nullptr;
                        run_->right = nullptr;
                        return;
                    }
                    else
                    {
                        run_ = run_->right;
                    }
                }
            }
        }
    }
    
   bool remove(T value){
    if(root_ == nullptr){
        return false;
    }
    else{
        node_t* param1 = nullptr;
        node_t* param2 = root_;
        while(1){
            if(param2->value == value){
                break;
            }
            else if(value > param2->value){
                param1 = param2;
                param2 = param2->right;
            }
            else if(value < param2->value){
                param1 = param2;
                param2 = param2->left;
            }
            if(param2 == nullptr){
                return false;
            }
        }
        if(param2->left == nullptr && param2->right == nullptr){
            if(param2 == root_){
                node_t* node = root_;
                root_ = nullptr;
                delete node;
            }
            else{
                if(param1->left == param2){
                    param1->left = nullptr;
                    delete param2;
                }
                if(param1->right == param2){
                    param1->right = nullptr;
                    delete param2;
                }
            }
        }
        else if((param2->left != nullptr && param2->right == nullptr) || (param2->left == nullptr && param2->right != nullptr)){
            if(param2 == root_){
                node_t* node = root_;
                if(param2->left != nullptr){
                    root_ = param2->left;
                }
                else if(param2->right != nullptr){
                    root_ = param2->left;
                }
                delete node;
            }
            else{
                if(param1->left == param2){
                    if(param2->left != nullptr){
                        param1->left = param2->left;
                        delete param2;
                    }
                    else if(param2->right != nullptr){
                        param1->left = param2->right;
                        delete param2;
                    }
                }
                else if(param1->right == param2){
                    if(param2->left != nullptr){
                        param1->right = param2->left;
                        delete param2;
                    }
                    else if(param2->right != nullptr){
                        param1->right = param2->right;
                        delete param2;
                    }
                }
            }
        }
        else if(param2->left != nullptr && param2->right != nullptr){
            node_t* node = param2;
            param1 = param2;
            param2 = param2->right;
            if(param2->left == nullptr){
                if(param2->right == nullptr){
                    node->value = param2->value;
                    param1->right = nullptr;
                    delete param2;
                }
                else{
                    node->value = param2->value;
                    param1->right = param2->right;
                    delete param2;
                }
            }
            else{
                while(param2->left != nullptr){
                    param1 = param2;
                    param2 = param2->left;
                }
                if(param2->right == nullptr){
                    node->value = param2->value;
                    param1->left = nullptr;
                    delete param2;
                }
                else{
                    node->value = param2->value;
                    param1->left = param2->right;
                    delete param2;
                }
            }
        }
        return true;
    }
}

    bool find(T value) const
    {
        if (root_ == nullptr)
        {
            return false;
        }
        else
        {
            node_t* run_ = root_;
            while (run_ != nullptr)
            {
                if (run_->value == value)
                {
                    return true;
                }
                else if (run_->value < value)
                {
                    run_ = run_->right;
                }
                else if (run_->value > value)
                {
                    run_ = run_->left;
                }
            }
            return false;
        }
    }

    node_t* root() const
    {
        return root_;
    }

    ~tree_t()
    {
        if (root_ != nullptr)
        {
            del(root_);
        }
    }

    void del(node_t* run_)
    {
        if (run_ != nullptr)
        {
            if (run_->left != nullptr)
            {
                del(run_->left);
            }
            if (run_->right != nullptr)
            {
                del(run_->right);
            }
            delete run_;
        }
    }

    void print(std::ostream& stream, node_t* run_, size_t u) const
    {
        if (run_->right != nullptr)
        {
            u++;
            print(stream, run_->right, u);
            u--;
        }
        for (size_t k = 0; k < u; k++)
        {
            stream << "--";
        }
        stream << run_->value << std::endl;
        if (run_->left != nullptr)
        {
            u++;
            print(stream, run_->left, u);
            u--;
        }
    }
};

template <typename T>
bool read(tree_t <T> & tree, std::istream& stream)
{
    char op;
    T value;
    if (stream >> op && (op == '=' || op == '+' || op == '?' || op == 'q'))
    {
        if (op == '=')
        {
            tree.print(std::cout, tree.root(), 1);
        }
        else if (op == 'q')
        {
            return false;
        }
        else if ((op == '+' || op == '?') && stream >> value)
        {
            if (op == '+')
            {
                tree.insert(value);
            }
            else if (op == '?')
            {
                std::cout << tree.find(value) << std::endl;
            }
        }
    }
    return true;
}
