###  简介：
  go 语言开发
  [知乎上关于docker的文章](https://www.zhihu.com/question/27227492)
  
  docker 是一个client－server程序.
    


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
  


### docker 参考书:
  第一本docker
