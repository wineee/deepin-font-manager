/*
 * Copyright (C) 2017 ~ 2018 Deepin Technology Co., Ltd.
 *
 * Author:     rekols <rekols@foxmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DFONTMANAGER_H
#define DFONTMANAGER_H

#include "signalmanager.h"

#include <QThread>
#include <QModelIndex>
/*************************************************************************
 <Class>         DFontManager
 <Description>   字体管理线程类-线程执行字体安装、批量安装、中途安装、重新安装、删除、批量删除等操作
 <Author>
 <Note>          null
*************************************************************************/
class DFontManager : public QThread
{
    Q_OBJECT

public:
    /*************************************************************************
     <Enum>          Type
     <Description>   操作类型
     <Author>
     <Value>
        <Value1>     Install                 Description:安装
        <Value2>     ReInstall               Description:重装
        <Value2>     UnInstall               Description:卸载
        <Value2>     HalfwayInstall          Description:中途安装
     <Note>          null
    *************************************************************************/
    enum Type { Install, ReInstall, UnInstall, HalfwayInstall};
    /*************************************************************************
     <Enum>          InstallStatus
     <Description>   安装状态
     <Author>
     <Value>
        <Value1>     InstallSuccess        Description:安装成功
        <Value2>     HalfwayInstallSuccess Description:中途安装成功
        <Value2>     Failed                Description:安装失败
     <Note>          null
    *************************************************************************/
    enum InstallStatus {InstallSuccess, HalfwayInstallSuccess, Failed};
    /*************************************************************************
     <Enum>          CacheStatus
     <Description>   fc-cache命令执行状态
     <Author>
     <Value>
        <Value1>     CacheNow               Description:立即执行
        <Value2>     CacheLater             Description:稍后执行
        <Value2>     NoNewFonts             Description:不执行
     <Note>          null
    *************************************************************************/
    enum CacheStatus {CacheNow, CacheLater, NoNewFonts};
    static DFontManager *instance();
    DFontManager(QObject *parent = nullptr);
    ~DFontManager();
    //设置线程执行类型
    void setType(Type type);
    //传入待安装字体列表
    void setInstallFileList(const QStringList &list);
    //传入待重装字体列表
    void setReInstallFile(const QString &reinstFile, const QString &sysFile);
    //传入待删除字体列表
    void setUnInstallFile(const QStringList &filePath);
    //更新待安装列表中系统字体的个数
    void setSystemFontCount(int systemFontCount);
    //执行fc-cache命令
    void doCache();
    //设置fc-cache命令执行的状态
    void setCacheStatus(const CacheStatus &CacheStatus);
    //更新线程停止状态标志位
    void stop();

signals:
    //批量安装信号
    void batchInstall(const QString &filePath, const double &percent);
    //安装完成信号
    void installFinished(int state, QStringList fileList);
    //重装完成信号
    void reInstallFinished(int state, QStringList fileList);
    //卸载完成信号
    void uninstallFontFinished(const QStringList &uninstallIndex);
    //卸载fc-cache命令执行完成信号
    void uninstallFcCacheFinish();
    //fc-cache命令完成信号
    void cacheFinish();

protected:
    //线程执行入口函数-安装、中途安装、重装与卸载
    void run();

private:
    //线程执行函数
    void doCmd(const QStringList &arguments);
    //字体安装-函数入口
    void handleInstall(bool isHalfwayInstall = false);
    //字体卸载-函数入口
    void handleUnInstall();
    //字体重装-函数入口
    void handleReInstall();
    //字体安装-具体执行函数
    void doInstall(const QStringList &fileList, bool reinstal = false);
    //字体卸载-具体执行函数
    void doUninstall(const QStringList &fileList);

private:
    SignalManager *m_signalManager = SignalManager::instance();
    QStringList m_instFileList;
    QStringList m_installOutList;
    QStringList m_uninstFile;
    QString m_reinstFile;
    QString m_sysFile;
    bool m_IsNeedStop = false;
    Type m_type;
    CacheStatus m_CacheStatus;
    int m_systemFontCount = 0;
};

#endif
