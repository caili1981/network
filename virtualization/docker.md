###  简介：
  go 语言开发
  [知乎上关于docker的文章](https://www.zhihu.com/question/27227492)
  
  docker 是一个client－server程序.
  docker 是一套工具集，本身并不算是虚拟化技术，而lxc (linux container) 才是虚拟化技术.
  
  ## cgourps 
    1.限制进程组可以使用的资源数量（Resource limiting ）。比如：memory子系统可以为进程组设定一个memory使用上限，一旦进程组使用的内存达到限额再申请内存，就会触发OOM（out of memory）。
    2.进程组的优先级控制（Prioritization ）。比如：可以使用cpu子系统为某个进程组分配特定cpu share。
    3.记录进程组使用的资源数量（Accounting ）。比如：可以使用cpuacct子系统记录某个进程组使用的cpu时间
    4.进程组隔离（Isolation）。比如：使用ns子系统可以使不同的进程组使用不同的namespace，以达到隔离的目的，不同的进程组有各自的进程、网络、文件系统挂载空间。
    5.进程组控制（Control）。比如：使用freezer子系统可以将进程组挂起和恢复。
    6.cgroups是一个树形层级关系.
    个人理解，cgroups提供了一种类似于hyperviser的资源管理系统。
    


### docker 命令
  1.  docker info 
      列出所有运行的docker程序。
  2.  service docker start | stop 
      启动docker守护进程。
  3.  docker [--name <user_defined_name> ]run -i  -t  <镜像名> <可执行程序路径>
      -d 可使容器后台运行.
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
      
  
       
  


### 其他
  1.  docker 参考书:
      <第一本docker>
  2.  cgroups: control groups。 lxc 就是基于cgroup的一种技术. 
