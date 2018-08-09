# 基本概念
  + sdn
    software designed network.
  + openflow
    - sdn里的主要协议. 最新是1.4.
    - 南向接口: 控制交换机。
    - 北向接口: 为服务提供可编程api. 如：多个控制器之间的通信问题，等等。
    - sdn的flowtable: 一组嵌套的rule组成。一个table的action可以被设定为下一跳. 
    - open-flow的三种消息控制类型:
      -  controller到交换机的消息。 用于controller控制网元设备.
      -  对称的消息。 一问一答的消息. 如hello报文.
      -  异步的消息. 类似于snmp里的trap消息，由交换机到控制器。 如packet-in 消息，由交换机发送到控制器。
      
    



# flow-table
  + action:
   - drop.
   - nat
   - go-to other table.
   - 发送给本地网络协议栈，或者转发给controller.
   - other  
  + 每一个flow-table都有一个默认的rule，用来应对所有rule都无法匹配的情况. 每一个rule都对应于一个优先级，匹配规则如下:
    - 优先级
    - 顺序
    - default
  + flow table 不一定非得储存所有的rule，可以通过packet-in来触发新流表的下发.
  + 
    
# openflow交换机
  openflow交换机和传统交换机的区别:
    1.  openflow的交换机和传统交换机应该都有acl和mac转发表？？？就是acl表和流表之间的区别?
    2.  


# other
  - IFmap (Interface for Metadata Access Points) 
    The IF-MAP protocol defines a publish/subscribe/search mechanism with a set of identifiers and data types.
  - 目前市面上的几种方案：
    1.  openflow + ovs
    2.  opendaylight + ovs.
    3.  contrail + vRouter. 
