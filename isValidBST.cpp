
#include<iostream>
#include<cstdlib>
#include<vector>
#include<queue>
#include<stack>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x):val(x),left(NULL),right(NULL){}
};

TreeNode *createTree(vector<string> serialization)
{
    TreeNode *root;
    int s = serialization.size();
    if(0 == s)
        return NULL;

    // Create a binary tree 
    int current_val = atoi(serialization.at(0).c_str());
    root = new TreeNode(current_val);
    int i = 1;
    queue<TreeNode *>q;
    q.push(root);
    while(i < s)
    {
        TreeNode *current = q.front();
        q.pop();
        string temp = serialization.at(i++);
        if(temp != "#")
        {
            TreeNode *come = new TreeNode(atoi(temp.c_str()));
            current->left = come; 
            q.push(come);
            cout<<"left:"<<come->val<<endl;
        }
        if(i < s)
        {
            temp = serialization.at(i++);
            if(temp != "#")
            {
                TreeNode *come = new TreeNode(atoi(temp.c_str()));
                current->right= come; 
                q.push(come);
                cout<<"right:"<<come->val<<endl;
            }           
        }
    }

    return root;
}

// 错误的解法：应该采用中序遍历，这样得到的结果才是从小到大排序的
//bool isValidBST(TreeNode *root)
//{
//    if(!root)
//        return true;
//    if(!root->left && !root->right)
//        return true;
//    if(root->left && root->right)
//    {
//        if(root->left->val>=root->val || root->right->val<=root->val)
//            return false;
//        return isValidBST(root->left) && isValidBST(root->right);
//    }
//    if(root->left && !root->right)
//    {
//        if(root->left->val>=root->val)
//            return false;
//        return isValidBST(root->left);
//    }
//    if(!root->left && root->right)
//    {
//        if(root->right->val<=root->val)
//            return false;
//        return isValidBST(root->right);
//    }
//}

// 正确的解法：采用中序遍历
bool isValidBST(TreeNode *root)
{
    if(!root || !root->left&&!root->right)
        return true;
    int pre;
    int cur;
    bool is_head = true;
    TreeNode *temp = root;
    stack<TreeNode *> st;

    while(temp)
    {
        while(temp->left)
        {
            st.push(temp); //节点暂时保存在栈中
            temp = temp->left;
        }
        if(is_head)
        {
            pre = temp->val;
            is_head = false;
        }
        else
        {
            cur = temp->val; // 找到左子树中无左孩子的节点（A）
            if(cur <= pre) // 必须满足升序要求
                return false;
            pre = cur;  
        }

        temp = temp->right; //去遍历A节点的右子树
        if(temp) //如果A节点的右孩子不为空，则继续按照上面的步骤，寻找A节点
            continue;
        if(!temp&&st.empty())
            break;
        // 出栈，访问这些节点（中序便利的规则） 
        while(!st.empty())
        {
            temp = st.top();
            st.pop();
            cur = temp->val;
            if(cur <= pre)
                return false;
            pre = cur;
            if(temp->right)
                break;
        }
        temp = temp->right;
    }
    return true;
}
void print(TreeNode *root)
{
    if(!root)
        return;
//    cout<<root->val<<" ";
    print(root->left);
    cout<<root->val<<" ";
    print(root->right);
}

int main()
{
    string str1[] = {"1", "#", "2", "3", "4", "5", "6", "7"};
    string str2[] = {"1", "#", "5", "4", "7", "#", "#", "6"};
    string str3[] = {"10", "5", "15", "#", "#", "6", "20"};
    string str4[] = {"0", "#", "1"};
    string str5[] = {"3","1","5","0","2","4","6","#","#","#","3"};
    string str6[] = {"0", "-1"};
    string str7[] = {"1", "1"};
    vector<string> vec(str7, str7 + sizeof(str7)/sizeof(str7[0]));
    TreeNode *root = createTree(vec);
    print(root);
    cout<<endl;
    if(isValidBST(root))
        cout<<"This tree is a binary search tree."<<endl;
    else
        cout<<"This tree is not a binary search tree."<<endl;

    return 0;
}
