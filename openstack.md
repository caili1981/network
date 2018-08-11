<openstack设计与实现>
xen有livert并不提供的一些特性，比如说资源池内的迁移。同一个物理硬盘映射的两个不同虚拟机，在迁移的时候是无需磁盘迁移的。
消息队列：
  一般实现远程过程调用RPC，是典型的生产者和消费者队列。
  对象化，后台有SQL数据库实现。python的对象可以被消息队列序列化成一个SQLtable。可以在SQLtable上建立索引，方便python查询。
  WSGI(web service gateway interface) 可以将不同的RESTful路由到不同的应用对象，然后将执行结果返回给用户。
  
eventlet: python的一个协程库。（非抢占行线程)
cliff:    command line interface formulation framework, 用来构建命令行程序的。

nova(虚拟机／computer资源管理）
  nova时openstack最早的项目之一，主要负责云端资源的管理，包括创建虚拟机、调度虚拟机，状态监控，热迁移等等。
  nova主要包括如下几个模块：
    
                  computer
                    |
    api    --- > queue ---> scheduler ----|db
                   |--->  conductor   ----|db
                   
    api是client对nova操作的接口
    computer是云中的虚拟机资源
    scheduler是云中的调度起，可以通过queue选择合适的computer资源。
    conductor是DB的一层封装以防止computer被攻破，恶意用户可以随意操作DB。
    一台机器默认的虚拟资源和物理资源的比例为：
          cpu core／virtual－cpu－core 位16:1. 
          内存利用率为1.5:1. 
    
swift （对象存储）
  主要用来存储静态，或者使用频率比较低的镜像。而实用频率比较高的对象，应该用块存储（cinder)

cinder (块存储).
  三种存储类型：
    1.  non-computer based distribute shared file system(磁盘阵列） 在线迁移方面没有太大的问题。
    2.  computer node based distrubte shared file system (？？？mount???)
    3.  本地存储。 在线迁移可能会存在问题。
  
# neutron
  － 三个模块:
    + API server.
      和交换机、路由器以及其他网络设备互操作的api. 存储网络DB.
    + plugins & agent.
      用于响应api－server，并创建网络。
    + message queue.
  - ovs不仅提供与linux bridge类似的功能，同时支持sdn，以及夸物理server的连接功能（一个物理服务器上的ovs可以透明的和另一个服务器上的ovs连接）
  
  - 每个节点（不管是computer node还是其他)，最少需要两个网卡。主要网络需求为：
    1.  内网访问。
    2.  外网访问。
    3.  存储访问。
    4.  租户内部网络等等。
   
   - ML2 (module layer 2)
   
   - address scope
     address scope 相当于tanent. 同一个address-scope可以互通。不同的address-scope通过nat互通.address-scope 内部地址不能重叠。address-scope之间的地址可以重叠。
    

# tap, tun, macVlan, macVtap
  + tap
    二层口。可以通过写文件的方式对报文进行操作。内核发送或者接收报文时，会将报文存入/dev/tap文件。
  + tun
    三层口。和tap类似，内核在接收报文时，会验证二层地址，并只将三层报文存入文件/dev/tun里。
  + macVlan
    为每个虚拟机网口生成不同的虚拟mac地址。网卡在收到报文时，会根据不同的mac地址，送入不同的虚拟机内核栈。
  + macVtap
    和macVlan类似，在送入虚拟机内核时， 或者发出虚拟机内核时，都会讲报文以文件形式展现给用户空间。便于用户进行操作。
  [详细讲义](https://blog.kghost.info/2013/03/27/linux-network-tun/)
  
# other concept
  + user, tenant, role
    - user: 用户
    - tenant: 用户组，对应一个部门.
    - role: 角色，普通用户，超级用户等等, 不同的role会绑定不同的权限。
