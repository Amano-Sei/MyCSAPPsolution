# c8

2020-3-17 夜 这里是荒废了一个假期的as...又说了一遍（修正了mysh中不会在停止的子进程收到sigcont之后修改状态的问题...发觉自己对waitpid或许有着不少误解（大概信号这里还是要找机会重学...

呀...因为各种各样的原因，这章的习题做的非常之慢...

(其实主要原因是开了iori限定我没抽到，然后爆肝还没抽到，另一方面是project euler我卡题了，需要的知识我到现在都没看完）

不过说实话最后的shell(下面用mysh代称)可以说非常有意思了，写下自己的疑惑和思考吧

本来计划的是不保存程序运行状态的标志位的，结果好像因为我知道的知道状态的方法只有通过第一次设置有WUNTRACED的waitpid，所以还是不得不给结构体增加了一个stat标志位

因为系统自带的shell在收到SIGINT(或SIGTSTP)之后会给前台进程组的每个进程都发送一个SIGINT(或SIGTSTP)，所以需要在调用execve前把子进程从mysh的进程组剥离出去

因为子进程会继承父进程的mask，所以需要把prev设置回去，而handler不会被继承，所以不需要重新设置

job是借助一个数组实现的，虽然每次删除当前运行的job都会引发大量移动，但是最多128个子进程所以问题不大？

因为SIGINT和SIGTSTP都不会直接修改job的数组，所以并不需要在对job修改时block它们

因为其实每轮只有一次对SIGCHLD进行的机会，所以其实我在想是不是不设置handler而是每轮固定waitpid

在形成了job体系之后bg和fg就是发个SIGCONT，改个stat

随着代码的推进，我把一部分重复代码抽了出来进行抽象，说到这个，因为我不想用csapp.h，所以自己写了个mysig.h和mysio.h，错误处理真的好麻烦啊（

整体来说，mysh还是写的非常开心的，文件夹里还有其他一些旧版本，是我各种错误的集合（但是又不舍得删...

不过这是c8的README嘛，其他的题，不需要代码依然没有放在这里，我也是和别的dalao的答案对过的答案，所以可以去参考别的dalao，代码部分这次的命名不像之前明确说明都是哪道题，而是大多以函数名命名

看了眼时间表（哇，这章我花了两周诶...emmm接下来应该会做shell lab

