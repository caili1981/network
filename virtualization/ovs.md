***基本篇***
  - 安装:
    apt update
    apt-get install openvswitch-switch
    apt-get install openvswitch-common
    apt-get install openvswitch-datapath-dkms 
  - code 安装.
    git clone git clone https://github.com/openvswitch/ovs.git
    sudo apt-get install autoconf automake libtool
    ./boot.sh
    ./configure
    make install
  - 启动:
    service openvswitch-switch start
    
 ***初级篇***
  命令：
    - ovs-vsctl ...
        ovs-vxctl show  
    - ovs-ofctl ...
    - 创建一个vxlan interface
        **ovs-vsctl add-port br1 vx1 -- set interface vx1 type=vxlan options:remote_ip=192.168.146.136**
 
    

    


***其他***
  - faucet
    sdn controller, 可以和ovs一起配合工作。
    yaml 文件，可以保存ovs的拓扑供controller使用。
  - ovn
    open virtual network. 和ovs类似，也是ovs的一个项目.
***注意事项***
  - ovs报文不走内核协议栈，所以tcpdump不能抓取报文.
  
    

