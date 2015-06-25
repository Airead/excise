ursa = require('ursa')

pubkey = """-----BEGIN PUBLIC KEY-----
MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDjVz84HLUOf0agqvAZi9Zmn+Lz
gj0zfd4kMIXmT+3pHSdaj4gexSrvBPV3xCh0pCBdHV+p+B3J5K8YUzmxMg4+XJEK
c5gk1t9K7FpJiIOXL6TKIkvUMx/ioppH2r4kon81uEDmA+41DPKfPb5wSZY0BHZv
2eofOsH/I7IOTAUmxQIDAQAB
-----END PUBLIC KEY-----"""
msg = 'Hello AireadFan'
console.log('message: ' + msg)

publicKey = ursa.createPublicKey(pubkey)
