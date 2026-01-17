# DSA - Digital Signature Algorithm

Chương trình mô phỏng thuật toán chữ ký số DSA.

##  Cách chạy chương trình

### Windows

**Cách 1: Sử dụng batch files (Đơn giản nhất)**

```bash
# Build chương trình
.\build.bat

# Chạy chương trình
.\dsa_program.exe

# Hoặc build và chạy luôn
.\run.bat

# Xóa file build
.\clean.bat
```

**Cách 2: Compile thủ công**

```bash
gcc main.c prime.c generator.c dsa.c -o dsa_program.exe -lgmp
.\dsa_program.exe
```

### Linux/macOS

```bash
# Build và chạy
make run

# Hoặc
make
./dsa_program
```

## Test Vector 

Kết quả chạy chương trình với p bắt đầu từ 2^511:

```
Nhap do dai cua so nguyen to p (L-bit, vi du: 512, 640, 1024): 512

Simulation of Digital Signature Algorithm

Global public key components are:

P (512 bits): 6703903964971298549787012499102923063739682910296196688861780721860882015036773488400937149083451713845164591926668660831156835712667261396847927957975513

Q (160 bits): 856747526304318829429293705536771727291759339959

G is: 0x9166b8ed90f3dd919f4c987765e583327df9b06f01677b557fb47f2cb9846bdb53e4e73accaefdbee4dee326a6e8039fb6711fc337ef85198098ee36216fa91

Secret information:
X (private) is: 0x4ed992e53f6d7e641778452b63f4a838b7b564d0
Y (public) is: 0x2e6e2db1bfd55825c830b5e1f160cd591142fd8d6ea79c521766e0409bb3fe666d21136482c10e7a416598851da18287f3444b66ac9d809bb97767b36fa8a902
H (mdhash) is: 0x4fc71b8f14431b1b1ce568a817b69ad49f0186ae

Generating digital signature:
DSA Signature Generated:
R is: 0x33564ec2fb293e7f3dde135039e61c270d18ed01
S is: 0x6c9698246348290632aa63a8a13ae25a3166e6b7

Verifying digital signature:
DSA Signature Verification Result: Valid

Success: Digital signature is verified!
R = 0x33564ec2fb293e7f3dde135039e61c270d18ed01
```
Kết quả của chương trình với p bắt đầu từ 2^639:

```
Nhap do dai cua so nguyen to p (L-bit, vi du: 512, 640, 1024): 640

Simulation of Digital Signature Algorithm

Global public key components are:

P (640 bits): 2281220308811097609320585802850145662446614253624279965289596258949637583604338693252956405658685699889321154786797203655344352360687718999127591676327014117148831966052345130379071160312810697

Q (160 bits): 1120420947231957299452737001929506278052135465633

G is: 0x50fc2ff7c0d3156218fa0ea6b0fd29dd6827393d33a28a84a9ccf0c7055305b4783059846086fc2e932eddf2e17de51194225d6642ac55e6c6605117236757fbcbabee38a5dbb5f702d359806aa24e0c

Secret information:
X (private) is: 0x46637c097ecd6c0baa06fd58399547b924f74322
Y (public) is: 0x4abf3dd1248258b22b513a86cec20fdb65e52c9cd920e9418a5ad3bafe6880a61e22c3eb84f3a4f034f62fb873bf390cd9279a6d67640a91171b10019caa1dadf7e5005799716140f7ff653567a0f5e6
H (mdhash) is: 0x485b7ab9bf1087ddceed0a996635b2bca1f1ef5a

Generating digital signature:
DSA Signature Generated:
R is: 0x728cb8bd91c903a2264691ceb46de5d62e970722
S is: 0x9b18105283b86322061fd3ea9e257e32dd46e489

Verifying digital signature:
DSA Signature Verification Result: Valid

Success: Digital signature is verified!
R = 0x728cb8bd91c903a2264691ceb46de5d62e970722
```
Kết quả của chương trình bắt đầu từ 2^575
```
Nhap do dai cua so nguyen to p (L-bit, vi du: 512, 640, 1024): 576

Simulation of Digital Signature Algorithm

Global public key components are:

P (576 bits): 123665200736552267030251260509823595017565674550605919957031528046448612553265933585158200530621522494798835713008069669675965342865738932948793238354168732031874579490425597

Q (160 bits): 1163378300483918614370700971970774260686289847491

G is: 0x132ae9296bb97d04228347822c1cc25e7548190550fd338dd0b17ebc1d0487879e9e769a2974aa8925a3c3200061760b140563b3361f0cea98deba5d7c91f1d6f6f9803df51a5750     

Secret information:
X (private) is: 0x209f2e936d83d5ee3e97334b69971b05fbcbae76
Y (public) is: 0x2c9dfda52b8ee0ad88117b9ce67b95089f4b5a3e2899b1194d7d112b1cc02b70a54b21ab8a5a0d12a57eca7697e25642f913da43b24b0035fc2d1954b5a9761bd331313cf565d622
H (mdhash) is: 0xc3bbeec9e6e4283ca820bf8e1f3027abd7a2261

Generating digital signature:
DSA Signature Generated:
R is: 0xcaa3563474988c325c7d3a132cd785cf00bc781c
S is: 0x5c4c7a108d82f7d02f8359c2fd9e42897e2a2ad2

Verifying digital signature:
DSA Signature Verification Result: Valid

Success: Digital signature is verified!
R = 0xcaa3563474988c325c7d3a132cd785cf00bc781c
```

**Giải thích:**
- **P**: Số nguyên tố L-bit được sinh từ 2^(L-1)
- **Q**: Ước số nguyên tố lớn nhất của (P-1)
- **G**: Generator của nhóm
- **X**: Khóa riêng (private key)
- **Y**: Khóa công khai (public key) = G^X mod P
- **H**: Hash của message (giả lập)
- **R, S**: Chữ ký số (signature)
- **Verification**: So sánh V với R để xác thực
