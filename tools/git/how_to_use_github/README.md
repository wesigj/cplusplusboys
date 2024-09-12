# how_to_use_github

[TOC]

## Overview

- Failed to connect to github.com port 443
- SSL certificate problem: unable to get local issuer certificate
- 不能访问 GitHub

---

## 1.问题：github访问不稳定或访问不了

- 搜索`Watt Toolkit`,安装并使用
- 选择代理模式
- 选择启用脚本
- 选择代理设置-代理监听IP地址-127.0.0.1

---

## 2.问题：Failed to connect to github.com port 443 after 21083 ms: Could not connect to server

在终端（命令行）中，设置代理端口即可

```bash
#设置代理端口
git config --global http.proxy 127.0.0.1:26561
git config --global https.proxy 127.0.0.1:26561
#查看代理端口
git config --global -l
#解除代理端口
git config --global --unset http.proxy
git config --global --unset https.proxy
```

---

## 3.问题：SSL certificate problem: unable to get local issuer certificate' when trying to clone repos

在终端（命令行）中使用以下指令

```bash
git config --global http.sslbackend schannel
```

---

## 4.schannel 与 openssl 区别

在Git中，`http.sslbackend` 配置选项用于指定在Windows上进行HTTPS操作时使用的SSL后端。`schannel` 是Windows提供的一组API，用于实现安全通道加密，它是Windows的默认SSL/TLS实现。

如果您在Windows系统上使用Git，并且希望确保Git使用schannel作为SSL后端，您可以使用以下命令来设置：

```bash
git config --global http.sslbackend schannel
```

这个命令会将Git的全局配置设置为使用schannel作为SSL后端。这意味着所有的Git操作，如克隆、拉取、推送等，都将使用schannel来处理HTTPS连接。

如果您遇到与SSL相关的错误，或者想要使用特定的SSL后端，您可以更改这个设置。除了`schannel`，Git还可以使用`openssl`作为SSL后端。如果您想切换回OpenSSL，可以使用以下命令：

```bash
git config --global http.sslbackend openssl
```

请注意，如果您的系统上没有安装OpenSSL，或者Git没有使用正确的路径来找到OpenSSL，这个命令可能会失败。

在更改SSL后端之后，您可能需要重新启动Git操作，以确保新的配置生效。如果您在公司或使用了特定的网络设置，您可能还需要确保您的网络策略允许您选择的SSL后端进行正确的通信。

在比较Schannel和OpenSSL时，有几个关键的区别和特点需要考虑：

1. **开源与专有**：
   - **OpenSSL** 是一个开源软件库，用于实现安全通信和加密算法。它的源代码对所有人开放，允许开发者和安全专家进行审查和修改，这有助于提高透明度和信任度。
   - **Schannel** 是Microsoft开发的专有安全通信组件，它是Windows操作系统的一部分。由于其代码不公开，用户无法自由审查代码，这可能会影响对它的透明度和信任度。

2. **跨平台与本地化**：
   - **OpenSSL** 是一个跨平台的库，可以在多种操作系统上使用，包括Linux、Unix、Windows等。
   - **Schannel** 特定于Windows操作系统，它利用Windows的内置加密功能，可能提供更好的性能和兼容性。

3. **算法和协议支持**：
   - **OpenSSL** 支持多种加密算法，包括对称加密算法（如AES和DES）和非对称加密算法（如RSA和ECC）。它还支持SSL/TLS协议的不同版本，以及其他安全相关的功能。
   - **Schannel** 提供对TLS 1.2、TLS 1.1、TLS 1.0、SSL 3.0和SSL 2.0等协议的支持，并且支持多种加密和散列算法。它通常与Windows操作系统的更新和安全策略保持一致。

4. **性能和稳定性**：
   - **Schannel** 作为Windows的一部分，可能会提供更好的性能和稳定性，因为它可以利用操作系统的优化和安全更新。
   - **OpenSSL** 则可能在不同的系统和配置中有不同的性能表现，但它的跨平台特性使其在多种环境中都能够得到应用。

5. **配置和管理**：
   - **Schannel** 的配置和管理通常通过Windows系统设置和策略进行，这可能使得在Windows环境中的集成和管理更加简单。
   - **OpenSSL** 需要单独安装和配置，可能需要额外的维护工作，但它的配置更加灵活，可以根据不同的需求进行调整。

6. **证书管理**：
   - **Schannel** 使用Windows系统的信任根证书颁发机构（CA）列表，这使得在Windows环境中管理证书更加方便。
   - **OpenSSL** 需要单独管理证书和CA列表，但这也提供了更多的控制和灵活性。

7. **安全性**：
   - 两者都提供了强大的安全功能，但是它们的安全性也取决于如何配置和使用。例如，Schannel可以自动检查证书吊销列表（CRL），而OpenSSL可能需要手动配置CRL检查。

在选择使用Schannel还是OpenSSL时，需要根据具体的应用场景、性能需求、安全要求以及操作系统环境来决定。对于在Windows环境中运行的应用程序，Schannel可能是一个更好的选择，因为它提供了与操作系统紧密集成的安全性。而对于需要跨平台支持的应用程序，OpenSSL可能是更合适的选择。

---

## 关于作者

- 微信公众号:WeSiGJ
- GitHub:[https://github.com/wesigj/cplusplusboys](https://github.com/wesigj/cplusplusboys)
- CSDN:[https://blog.csdn.net/wesigj](https://blog.csdn.net/wesigj)
- 微博:
- 版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。

<img src=/./img/wechat.jpg width=60% />
