# proxy lab

首先是pp的名字，PP proxy server。

出身自写的贼烂的第12章课后作业，然后被简单重构了下，自认为当时的结构还算是不错。

但是随着缓存模块的强行加入，感觉出现了不少的重复代码...但是本身的代码顺序也不知道怎么调整才能更好一点。

第一二部分基本上和课后作业是一样的，所以就着重介绍下缓存模块。

缓存模块只提供了三个函数给其他模块调用，insert，update和get。

insert的话其实会因为写者同时只会有一个，所以没必要进一步加锁（然后我给去了。

update和get都是读者的操作，但是update不会操作hash表，所以不需要保证update和get互斥，而update本身是需要互斥的。

所有的缓存操作都是建立在自己的一个cbuf上的，除了读者写者基本模型的信号量外，给hash表也有一个linkmutex供update互斥操作。

每一个独立的缓存都是一个ccb，每一个ccb都由一个url进行标识，通过url计算hash值插入对应的链表。

所有的ccb除了串成一个按照最后访问顺序排练的双向循环链表外，还在自己对应hash值的链表中。

每一个连接首先是一个读者借助url访问hash表寻找是否有自己想访问的内容，如果有就把内容发给连接，并把这个ccb重新插入到循环链表的尾部，否则向url对应的服务器进行请求，并且同时转发给连接。如果一切正常，响应大小也满足限制，且从服务器获取的响应状态码在200-299的范围内，那么我们就成为写者缓存这个内容。在插入时，如果总缓存大小超过限制，我们会不断释放首部的ccb，直到我们可以插入这个ccb。

需要注意不是文本文件的话是完全有可能出现'\0'的，所以不能用strlen和strcpy来处理，如果获取内容的时候放在函数里面，那么就只能要么想办法传指向内容的指针和内容的长度两个东西出来，要么直接在那个函数里面搞缓存。

大致就这样。

我们可以看到driver.sh只是对功能进行基本的检查，但是信号量的同步互斥是否会出现问题我们并不知道（最少我认为我这样写是没问题的。

测试的时候没少打开www.cplusplus.com，毕竟现在http网站不多了\(在缓存后即使断网也秒开，开心

