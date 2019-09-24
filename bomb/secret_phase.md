关于secret_phase，起初自己以为又要读汇编代码
但是skip的14个跳转点和各种奇妙的参数传递还是成功压垮了我...

搜了下dalao们的做法，明白了读汇编的代价确实太大了，这样做虽
然不是不能做，但是时间代价太大了

0x603760的话我一开始就猜到了是id，但是没有验证的意识
0x603870是某次输入的字符串大概也猜到了，虽然理由在自己重新审
视他的时候发觉是错误的噗...
而且不知道看到那个dalao写的博客说什么攻击误导了我以为存在什么
buf溢出攻击（

所以为了用最小的代价完成bomb lab，我们开始正确的攻略方式


首先是验证0x603760，借助display和在read_line收尾设置breakpoint
就可以断言应该确实在read_line中存在对0x603760的修改，这也打消了
我起初判断会死循环的疑虑
（因为我没有系统地学过汇编，以为%rip中是当前指令的地址，纠结了好
久。后来查阅了amd文档2.2.5节RIP-Relative Addressing中有提到"The 
effective address is formed by adding the displacement to the 64
-bit RIP of the next instruction."至此疑虑彻底打消。

然后是确认0x603870，方法和0x603760一样（通过输入格式是"%d %d %s"，
可以如果真的如我们猜测是某次的字符串的话可以断言应该会在phase_3和
phase_4的字符串中
经过验证，是phase_4的字符串，把他加入我们的第四个答案中
输入新的1~6的答案，成功进入secret_phase...

接下来就简单多了，查看反汇编的secret_phase的代码，他读入了一行按照
十进制把他转化成一个long，然而事实上只用了低四字节，也就是int的大小
他需要在0x000001~0x40126d之间，然后以0x6030f0和这个数依次作为两个参
数调用fun7。

fun7的调用和0x6030f0~0x6032d0为止的数据让我们不禁想起二分查找，把这
个数据按照四个4字一组，第一个是数据项，第二个第三个分别是左子树和右
子树指针，很轻易的得出一组答案20或22
然后经过分析，好像只有这两个答案...本来想着-1的存在会很头疼准备好穷
举了，然而是我开始想错了
