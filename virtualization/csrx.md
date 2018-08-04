   **csrx & vsrx 区别** 
   - csrx只提供L4功能，并不提供L3相关功能(vsrx提供)，从而避免service chain上的重复功能.
   - csrx直接运行在Linux裸机上，基于docker. vsrx 是基于kvm，启动速度更快，占用资源更小.
   - csrx目前只提供一进一出两个端口。而vsrx则提供多个端口.
   - 在csrx中，所有daemon直接运行在linux主机上，而不是unix上。并不是所有vsrx中运行的daemon都会在csrx中运行。
     interface/route/routing-instance/mpls/vlan/nat/vpn/multi-cast 等都不会在csrx中运行。
   - csrx的大小(585M) 远比vsrx小(2.8G)
     csrx 使用联合挂载技术，除/var /config之外的很多volume可以被其他容器共享，这样进一步减小了容器所占用的磁盘空间.
   - 错误处理
      csrx 的flowd出错，报文会被bypass(monitoring process will signal to host OS)，也就是说，不会导致流量出问题。
      flowd 重启后，如果sync check 关闭，则流量可以恢复。
      也可以通过shared－memory来进行session & gate的恢复，flowd重启，重新attach上这片shared-memory.
   - csrx 应用模型
      1.  vm直连
      2.  switch之间
      3.  路由器之间. 
      都是transparent－mode
      
   
 csrx 三种模型:
   -  Low/mid
      端口运行在tap模式下。中断模式收报文，适合高密度部署。
   -  high
      端口运行在dpdk模式下, 需要专有的dpdk-port, dpdk是死循环，因此会导致host-server性能出现瓶颈，不适合高密度部署。
      
      
 CSRX 内核参数：
   -  GRO/LRO
      ethtool -K eth0 gro off
   -  并发连接数
      sysctl -w net.netfilter.nf_conntrack_max=1000000
   -  tcp timeout
      sysctl -w net.netfilter.nf_conntrack_tcp_timeout_established=1000000
   -  ARP
      sysctl -w net.ipv4.neigh.default.gc_thresh1=1024
      
  CSRX packet driver:
    - dpdk based poll mode driver
    - interupt based driver
  
  CSRX performance
    - throughput
      1.8G (dpdk)  vs 1.5G (interrupt driver).
    - start/down time
      3 second (start) vs 1 second(stopp).
      




 **other**
  cat repositories.json | python -json.tool    ===> 这个命令可以以树形格式查看json文件，很方便。
  
  
 **docker相关**
  root@ubuntu-stable:/var/lib/docker/image/aufs# cat repositories.json | python -m json.tool     ===> 这个地方存放docker-image名称。 
  docker images输出的imageid，实际上是docker sha的前几位。
  https://segmentfault.com/a/1190000009730986 image的层次讲的比较清楚。
  
  
