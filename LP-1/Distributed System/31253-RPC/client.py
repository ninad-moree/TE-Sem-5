import xmlrpc.client
proxy = xmlrpc.client.ServerProxy('http://localhost:7500/')
print("factorial of 3 is : %s" % str(proxy.factorial_rpc(3)))
print("factorial of 5 is : %s" % str(proxy.factorial_rpc(5)))
print("square of 15 is : %s" % str(proxy.square_rpc(15)))
