# 简介：
  + go 语言开发
  + [知乎上关于docker的文章](https://www.zhihu.com/question/27227492)
  
  - docker 是一个client－server程序.
  - docker 是一套工具集，本身并不算是虚拟化技术，而lxc (linux container) 才是虚拟化技术.
  
# 基本知识   
  + cgourps 
    1.限制进程组可以使用的资源数量（Resource limiting, cpu，内存，io等）。比如：memory子系统可以为进程组设定一个memory使用上限，一旦进程组使用的内存达到限额再申请内存，就会触发OOM（out of memory）。
    2.进程组的优先级控制（Prioritization ）。比如：可以使用cpu子系统为某个进程组分配特定cpu share。
    3.记录进程组使用的资源数量（Accounting ）。比如：可以使用cpuacct子系统记录某个进程组使用的cpu时间
    4.进程组隔离（Isolation）。比如：使用ns子系统可以使不同的进程组使用不同的namespace，以达到隔离的目的，不同的进程组有各自的进程、网络、文件系统挂载空间。
    5.进程组控制（Control）。比如：使用freezer子系统可以将进程组挂起和恢复。
    6.cgroups是一个树形层级关系.
    个人理解，cgroups提供了一种类似于hyperviser的资源管理系统。
    
    ***docker的cgroup的资源控制在目录:/sys/fs/cgroup/cpu/docker/<container_id>/ ***
    
    
  + namespace 分类
      1.  uts<主机名、域名> ??? 为什么起这个名字？
      2.  ipc 信号量，消息队列，内存共享。
      3.  pid 每个不同的namespace里都有一个root进程. 
          父namespace可以看到子namespace的进程，但是子namespace无法看到父namespace的进程.
          为了避免孤儿进程，容器内部第一个启动的进程(init)应该具有监控和回收能里，如bash等.
          init进程还可以进行信号屏蔽和传递。 父节点(namespace)如果发送sigkill/sigstop给子节点，那么子节点会将所有进程全部销毁。
          
      4.  network 
          通过veth连通不同的namespace的网络，以达到通信目的。
      5.  mount
          mount的类型可以分为:
          -  共享挂载
              挂载目录的变化能够被其他节点感知。 /lib 目录。
          -  从属挂载
              父节点的挂载文件的变化可以被子节点感知，反之则不行。 /bin 目录.
          -  不可挂载
              /root目录就属于不可挂载的。
      6.  user & user-group
          《docker容器与容器云》编写时仍不成熟。
          
  + API
      1.  clone
          flags: CLONE_NEWIPC CLONE_NEWUTS CLONE_NEWNET
      2.  setns
          
      3.  unshare
          调用者停留在当前的namespace，而被调用着进入新的namespace.
          
  + etc
      1.  ls -al /proc/<pid>/ns/


# docker 命令
  1.  docker info 
      列出所有运行的docker程序。
  2.  service docker start | stop 
      启动docker守护进程。
  3.  docker run -i  -t  [--name <user_defined_name> ] <镜像名> <可执行程序路径>
      -d 可使容器后台运行.
      docker run [options] image [command] [args] 
  4.  docker start <container_name>
  5.  docker attach <container_name> 附着在容器上.
  6.  docker top <contain_name> 
      查看容器内部进程.
  7.  docker exec -d <container_name> <process> 
  8.  docker inspect <container_name> 
  9.  docker rm <container_name>
  10. docker pull <image_name:ver>
      从镜像仓库(docker hub)获取一个镜像. 如果没有指定版本号，则取最新的版本.
  11. docker search <image-name> 
      从镜像仓库里查找一个镜像. 
  12. docker commit
      能够将一个容器的内容提交，以便以后的docker pull使用。 * 这种方式已经不推荐使用, 最好使用dockerfile *
  
  13. docker 仓库
      [docker仓库，上面有很多知名软件的docker仓库，可以直接用](https://registry.hub.docker.com/) 
      
  
       
  


# 其他
  + docker 参考书:
      <第一本docker>
      <docker 容器与容器云> 这本书对原理的阐述比较到位. 
  + cgroups: control groups。 lxc 就是基于cgroup的一种技术. 
