#!/usr/bin/env python3

import random
import math
import hashlib
import secrets
import hmac
from time import sleep
from threading import Thread
from queue import Queue

gt = 0 # time
n = 5 # number of keys in a chain excluding k0
d = 2 # key disclosure delay
k0 = '' # commitment 
buf = [] # receiver's buffer

class Key:
	def __init__(self, index, k):
		self.index = index
		self.k = k	
	def __str__(self):
		return f"index is '{self.index}', key is '{self.k}'"
	
class Packet:
	def __init__(self, index, message, mac, keyObj):
		self.index = index
		self.message = message
		self.mac = mac
		self.keyObj = keyObj
	def __str__(self):
		return f"packet: index is '{self.index}', message is '{self.message}', mac is '{self.mac}' keyObj is {self.keyObj}"
	
def sha(x):
	m = hashlib.sha1()
	m.update(str(x).encode())
	return m.hexdigest()

def mac(m,k):
	h = hmac.new(k.encode(), m.encode(), digestmod='sha1').hexdigest()
	return h

def gen(size):
	x = secrets.token_hex(1000) # 1KB random value
	chain = [Key(0, sha(x))]
	for i in range(size):
		k=sha(chain[i].k)
		chain.append(Key(i+1,k))
	return chain

def isValidKey(k):
	someKey = sha(k)
	for i in range(n):
		if k0 == someKey:
			return True
		else:
			someKey = sha(someKey)
	return False

# sender task
def sender(queue):
	global k0 
	global gt
	keys = gen(n)
	
	for i in range(n+1):
		print(keys[i])
	
	k0 = keys[-1].k # last key
	print('sender: Running')
	for i in range(1,n+1):
		sleep(1)
		m = f'message {i}'
		ko = keys[-(i+1)] 
		h = mac(m,ko.k)
		p = Packet(i, m, h, keys[-(i-d+1)] if gt > 1 else None)
		queue.put(p)
		gt = gt + 1
		print(f'>sender: packet sent {p}')
	# signal that there are no further items
	queue.put(None)
	print('sender: Done')
	
# receiver task
def receiver(queue):
	print('receiver: Running')
	while True:
		newPacket = queue.get()
		# check for stop
		if newPacket is None:
			break
		print(f'>receiver: got the packet')
		if gt > d:
			oldPacket = buf[gt-d-1]
			k = newPacket.keyObj.k
			if isValidKey(k):
				if mac(oldPacket.message,k) == oldPacket.mac:
					print(f"receiver: authentication successful for '{oldPacket.message}'")
				else:
					print(f'receiver: authentication failed')
			else:
				print(f'receiver: invalid key')
		buf.append(newPacket)
		
	print('receiver: Done')
	
# create the shared queue
queue = Queue()
# start the receiver
receiver = Thread(target=receiver, args=(queue,))
receiver.start()
# start the sender
sender = Thread(target=sender, args=(queue,))
sender.start()
# wait for all threads to finish
sender.join()
receiver.join()