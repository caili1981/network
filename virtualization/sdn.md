***基本概念***  
  sdn
    software designed network.
  openflow
    sdn里的主要协议. 最新是1.4.
    南向接口: 控制交换机。
    北向接口: 为服务提供可编程api.
    sdn的flowtable: 一组嵌套的rule组成。一个table的action可以被设定为下一跳. 
    
    



# flow-table
  action:
   - drop.
   - nat
   - go-to other table.
   - other  
  
