# shell lab

这里是~~还没有开始就已经~~发生了一点小插曲的as :joy:

因为之前我给习题写的mysh是限制了最大子进程数的，但是writeup中说任意个进程

所以在tshref中试了下，结果最多16个，但是...虽然提示说`Tried to create too many jobs`，但是事实上他还是创建了（而且jobs里面没有，而且用fg和bg都提示说`No such process`，而且如果quit时，还有没有结束的进程，那么也不会被回收（而且这个时候如果不输入builtin\_command的话会不停提示过多jobs，而且输出是乱的，而且sh套sh会stop，导致停止的信号是SIGTTIN，一口气说了好多（

不过这些都是小插曲，正片是我突然想到那么我自己机子上的shell可以创建多少个子进程呢，然后在我创建了1w多一点的时候，提示说fork:重试等待资源什么的，这个时候我ctrl+alt+t连个shell都叫不出来了（想ps看都有什么也要等待资源...即使我关掉那个shell也还是一卡一卡的（通过系统监视器把之前在tshref中没有被回收的一百多个子进程kill掉也没有什么变化...最后只得重启（不亏是完成品的shell，只要能创建，就能一直创建，不能创建还要等到能创建再创建

其实tsh在昨天（2019-11-19)就已经写完了，但是当我看表的时候已经是十点了（如果锁门的话）我已经被宿管锁外面了，所以赶快跑了回去，因为最近又开始了早起，所以回去就睡了，然后今天上午又被web前端的作业折腾了一上午（真的忘完了...等到中午才开始，然而我现在还没吃饭(utc+8 13:30)，还因此冷死了QAQ

写了一个lastsh.sh，用于最后的测试和比较，最终输出都在lastshoutput里面，可以看到除了pid和一些脚本名以外和ref输出是完全一样的，摸着良心说，这个比mysh写起来简单多了...大框架给了，提示也那么多，我自己的mysh是参考自己机子上的shell行为来写的，所以fg和bg没有参数的话会使用最后一个前台进程，这边自然是和ref identical的。

可惜这个没有明确的评分器什么的，虽然我diff了两者的输出，但是最后的判断还是肉眼来进行的...应该算是过了吧（可以说是自bomb lab之后第一次这么顺的lab了...

不过说实话linux信号，系统调用这些东西并不能就这样说过了，csapp在这里讲的感觉更多的是一个领进门的感觉

马上要期末了，c9也是很重要的一章（你说哪一章不重要），随着章节的推进，感觉自己对于系统也开始一点点有了自己的认识，说实话这一章相当有趣，只是缺陷版的sh就已经让我非常兴奋了，更不用说mysh的完成←明明你因为没有抽到iori一度自暴自弃...虽然作为收尾的shell lab没有那么大的成就感，但是也算是让自己知道自己写的sh是否具有正确性，作为当下阶段的sh或许已经足够了

本来是有一段负能量的，但是写出来之后就没那么气了，所以还是删了，而且发觉自己总结因为负能量跑偏了（

嘛，还是要多努力多读书少说话
