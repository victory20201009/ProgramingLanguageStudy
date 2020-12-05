<center><font color="#FFA500" size="6">spring framework overview</font></center>

[TOC]

# 1 spring framework概述

spring框架是一个模块化的组织架构，由 7 个定义良好的模块组成。Spring 模块构建在核心容器之上，核心容器定义了创建、配置和管理 bean 的方式。如下图所示：

<img src="img/spring_framework.gif"/>

组成spring framework的每一个组件都可以单独存在，又可以联合起来使用，每一个组件的概述如下：

## 1.1 spring core

核心容器提供 Spring 框架的基本功能。核心容器的主要组件是 `BeanFactory`，它是工厂模式的实现。 `BeanFactory` 使用 **控制反转 （IOC）** 模式将应用程序的配置和依赖性规范与实际的应用程序代码分开。

## 1.2 spring context

spring上下文，起到辅助作用，携带一些全局的消息，可以向spring framework提供上下文信息。Spring 上下文包括很多企业服务，例如 JNDI、EJB、电子邮件、国际化、校验和调度功能。

## 1.3 spring aop

面向方面编程

> 通过配置管理特性，Spring AOP 模块直接将面向方面的编程功能集成到了 Spring 框架中。所以，可以很容易地使 Spring 框架管理的任何对象支持 AOP。Spring AOP 模块为基于 Spring 的应用程序中的对象提供了事务管理服务。通过使用 Spring AOP，不用依赖 EJB 组件，就可以将声明性事务管理集成到应用程序中。

## 1.4 spring dao

访问数据库，注意对异常处理做了封装，提供了有意义的异常层次结构，可用该结构来管理异常处理和不同数据库供应商抛出的错误消息，简化了数据库的异常处理逻辑

## 1.5 spring orm

Spring 框架插入了若干个 ORM 框架，从而提供了 ORM 的对象关系工具，其中包括 JDO、Hibernate 和 iBatis SQL Map。所有这些都遵从 Spring 的通用事务和 DAO 异常层次结构。

## 1.6 spring web

Web 上下文模块建立在spring context之上，为基于 Web 的应用程序提供了上下文。所以，Spring 框架支持与 Jakarta Struts 的集成。Web 模块还简化了处理多部分请求以及将请求参数绑定到域对象的工作。

## 1.7 spring mvc

MVC 框架是一个全功能的构建 Web 应用程序的 MVC 实现。通过策略接口，MVC 框架变成为高度可配置的，MVC 容纳了大量视图技术，其中包括 JSP、Velocity、Tiles、iText 和 POI。