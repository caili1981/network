   **csrx & vsrx 区别** 
   - csrx只提供L4功能，并不提供L3相关功能(vsrx提供)，从而避免service chain上的重复功能.
   - csrx直接运行在Linux裸机上，基于docker. vsrx 是基于kvm，启动速度更快，占用资源更小.
   - csrx目前只提供一进一出两个端口。而vsrx则提供多个端口.
   - 在csrx中，所有daemon直接运行在linux主机上，而不是unix上。并不是所有vsrx中运行的daemon都会在csrx中运行。
     interface/route/routing-instance/mpls/vlan/nat 等都不会在csrx中运行。
   - csrx的大小(585M) 远比vsrx小(2.8G)
     csrx 使用联合挂载技术，除/var /config之外的很多volume可以被其他容器共享，这样进一步减小了容器所占用的磁盘空间.
   
 csrx 三种模型:
   -  Low/mid
      端口运行在tap模式下。中断模式收报文，适合高密度部署。
   -  high
      端口运行在dpdk模式下, 需要专有的dpdk-port, dpdk是死循环，因此会导致host-server性能出现瓶颈，不适合高密度部署。
      
      
