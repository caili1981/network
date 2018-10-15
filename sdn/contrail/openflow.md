### 概要
  - 与传统网络的区别
    - openflow是基于集中控制的，类似于以前的atm。而传统网络是分散控制的，每个网络设备自主完成下一跳的转发.
    - openflow的设计时控制和转发完全分离的，所有的转发都是通过流表来完成, 功能单一化，但是controller性能是瓶颈。而传统网络的转发，都是通过各自的协议来完成, 功能复杂。openflow交换机，再没有所谓的协议转发，取而代之的只有流表转发。但是协议转发并不是就不存在来，只是由openflow交换机转移到openflow控制器了.
    - 在虚拟化环境中，通过openflow的方式，可以避免无休止的网络配置
      > 例如，如果需要动态申请一台vm时，只需要通过openflow下发流表即可。而不需要对端口进行vlan/vxlan的配置.
    - 一个网络中，openflow的控制器也可以有多个，从而缓解控制器的压力. 
      > 这是分而治之的策略，例如: vlan100 可以对应控制器A, vlan200对应控制器B. (flowvisor)
  - 流表
    > 类似于policy/acl. 不同的是policy/acl并不参与转发，但是流表是转发控制. 
    > 一个流可以匹配多个流表，也可以同时匹配一个流表中的多个流表项(1.1之后支持)
    > 流表有多个，先从0号流表开始匹配。
    > 如果所有流表都匹配不到，则可能发生packet-in(触发reactive配置)/table-miss, 具体触发那种操作，需要根据配置决定.
  - 流表的下发
    - proactive 
      > 控制器主动发给各个openflow交换机.
    - reactive
      > openflow遇到无法处理的报文，则请求控制器进行指示.
      > 控制器处理完后，可能像多台openflow交换机发送流表. (一个交换机触发，可能多台受益).
  - openflow交换机和控制器之间的连接
    - TLS(标准做法)
    - TCP(1.1之后支持明文，事实上tls的开销过于庞大).
  - openflow协议
    - tcp/TLS连接建立
      - 安全连接出错时，会重新试图创建新连接.
      - 如果仍无法创建新的安全链接，则进入紧急事态模式。所有openflow交换机的普通流表项都会被删除.
    - hello
      > 协商版本
    - 握手
      > 所支持的feature协商，控制器发往openflow交换机.
    - flow-mod
      > 添加/删除流表
    - packet-in
      > table-miss/action是发送到控制器时，将报文发送给控制器.
    - packet-out
      > 包含数据包发送命令.
    - port-status
      > 添加／删除端口状态.
    - flow-removed
      > 流表超时.
    - Error消息
    - echo
### lldp (link layer discover protocol)
  > 用来检测链路层拓扑
