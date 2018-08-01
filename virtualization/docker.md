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
    
    **docker的cgroup的资源控制在目录**:/sys/fs/cgroup/cpu/docker/<container_id>/
    
    
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
  
# docker 存储.
  - aufu (advanced multi layer unification filesystem)
    联合挂载技术.
    联合挂载技术的缺点：
      1.  宿主机无法对文件进行方便管理。
      2.  挂载点跟随操作系统，docker 实例删除时会出现问题。
      3.  多个容器之间无法共享
    为改进如上缺陷，引入volume机制。
      1.  容器创建就初始化。
      2.  能在不同容器间重用。
      3.  独立于docker的生命周期。
      4.  对volume操作不影响镜像
      docker volume 实际上就是在创建镜像时，在镜像文件系统中mount一个文件夹。
        （是不是对volume的文件进行操作时，其修改并不会跟随docker commit命令。是不是可以用来存储用户操作相关文件，类似于普通磁盘和系统盘？
        
# docker 网络管理
  - 内置驱动
      1.  bridge.
          和普通虚拟机的bridge方式类似。
      2.  host.
          直接利用host网络。
      3.  overlay.
          vxlan
      4.  remote
          用户自行注册。
      5.  null
          只创建loopback接口。
      6.  nat模式
          container 通过eth1 连接宿主机的veth, 然后通过iptables进行nat转换。
      7.  other container.
          host & nat的组合. 
          container2 用 container1的ip & mac & namespace. container1 出docker的时候用nat。
          用于容器之间通信非常频繁的情况。
  - docker netowrk 命令
    + docker netowrk connnect <bridge_name>  <container_name>
      通过这个命令可以将一个docker容器连接入一个交换机. 这个交换机上有dhcp的功能，能自动为docker分配ip地址。
    + docker netowrk   
          
# docker 暂未实现的虚拟化
   -  time
   -  syslog
   -  dev
   -  proc
   -  sys
   -  系统调用
      可以通过 seccomp 来限定docker虚拟机系统调用的范围。
   由此可见，docker离真正的虚拟化尚有一定距离。
  
# docker 关键概念
  - registry.
      存放所有镜像的网站。 如: hub.docker.com 
  - repository
      一组具有特定功能的镜像组.  如jackcai/ubuntu
  - manifest.
      元文件清单。保存镜像所修改过的文件清单。
  - image/layer.
      镜像的分层关系。  一个特定的镜像，可能是存放在某一个用户名下的，具有多个分层结构的镜像。
      所有一个镜像可以通过  registery/repository/image-layer1/image-layer2/xxxx 来进行表示。
  - docker file.
      docker commit: 提交一个镜像到registry上
      docker build:  在本地创建一个基础镜像.
      docker export: 用户持久化容器，会丢失所有的历史。
      docker save-loaded: 则会在本地保存容器的历史层，以方便回滚。
      docker push：  上传容器到仓库。
      docker pull:  下载容器到仓库。
      
# docker 安全
  - 磁盘资源限制。
      docker虚拟机上的文件其实也是宿主机上的一个文件，如果不加以限制则可能出现一个虚拟机把宿主机磁盘耗尽的情况。
  - 容器逃逸
      通过某些系统api如open_by_handle_at暴力调用系统api，获取宿主机的敏感文件。
  - 网络共享，ddos攻击等。
  - 
  
# dockerfile
  类似于脚本，可以创建和编辑docker镜像。
  ## docker build -t <image_name> ./   
  也可以通过docker commit <container_name> <image:tag> 来创建image，这种方式比较灵活，能够自动纪录所有修改，而不需要写dockerfile脚本。
      
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
  10. docker pull/push <image_name:ver>
      从镜像仓库(docker hub)获取一个镜像. 如果没有指定版本号，则取最新的版本.
      docker push will only push the image to registry. If you installed some software in the instance, it will not push to registry server. 
  11. docker search <image-name> 
      从镜像仓库里查找一个镜像. 
  12. docker commit
      能够将一个容器的内容提交，以便以后的docker pull使用。 * 这种方式已经不推荐使用, 最好使用dockerfile *
  
  13. docker 仓库
      [docker仓库，上面有很多知名软件的docker仓库，可以直接用](https://registry.hub.docker.com/) 
      
      
  14. docker-compose 
      docker编排工具. 编辑一个docker-compose.yml 文件即可。
      使用于单主机的情况，但是对于跨主机的部署和编排，docker-compose能力有限。
      docker-machine
      可以用于控制docker宿主虚拟机，支持vmware／virtualbox等. 类似于libvirt???
      swarm: 用于操纵多台docker宿主机。
      
  15. docker tag
      将本地image归入某一个仓库。
      
      
      
  16. docker network ls
   
  17. docker search <xxx> 
      docker hub查找镜像

# dockerfile
  1.  docker run/dockerfile cmd/entrypoint 区别
    - CMD:
      docker启动的默认命令, 只有最后一条生效
    - docker run
      docker启动时指定的参数，会讲cmd命令覆盖。
    - entry point
      如果docker run不指定命令执行参数，则执行entry-point所指定的命令，如果docker－run指定了启动命令，则将docker-run 指定的命令作为参数，传给entry-point, entry point 比较灵活，可以和docker run结合起来，为运行时传递参数。     
      
  2.  WORKDIR 参数
    指定工作目录. docker run -w 会覆盖WORKDIR的工作目录
  
  3.  ENV
    指定环境变量. docker run -e 会覆盖同样的环境变量。
  
  4.  USER
    指定镜像会运行的用户.
  
  5.  VOLUME
    添加卷。 docker run -v提供同样的功能。
    
  6.  ADD命令
    将dockerfile文件夹下的文件拷贝到镜像中.
    
  7.  COPY
    和ADD类似，但是不提供解压的功能。
  
  8.  ON BUILD
    镜像在被别的镜像作为基础镜像时触发。
    只会在子镜像中执行一次，不会在孙子镜像中执行。
    
    
      
# 其他
  + docker 参考书:
      <第一本docker>
      **<docker 容器与容器云> 这本书对原理的阐述非常到位. **
      
  + cgroups: control groups。 lxc 就是基于cgroup的一种技术. 
  
  - ip netns exec <net_namespace> <command> 
    用来对namespace的网络进行配置。
  - nsenter 进入容器，不同于docker attach（这个命令离开就会停止容器，且不能多个窗口登陆容器)
      $ docker inspect -f {{.State.Pid}} 容器名或者容器id   #每一个容器都有.State.Pid，所以这个命令除了容器的id需要我们根据docker ps -a去查找，其他的全部为固定的格式
      $ nsenter --target 上面查到的进程id --mount --uts --ipc --net --pid  #输入该命令便进入到容器中
  - etcd
    用于键值存储，和服务发现，提供了丰富的注册和watch机制。
    raft分布式一致性算法，分布式时序控制等等。
    
  
