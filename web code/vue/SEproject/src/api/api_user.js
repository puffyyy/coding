/**
 * Created by guxin on 2018/09/13.
 * 用户相关api
 */
import * as API from './'

export default {
    //注册
    register: params => {
        return API.POST('/api/users/add', params)
    },
    //登录
    login: params => {
        return API.POST('/api/users/login', params)
    },
    //登出
    logout: params => {
        return API.GET('/api/users/logout', params)
    },
    //修改个人信息
    changeProfile: params => {
        return API.POST('/api/users/put', params)
    },

    findReadersByKeyword: params => {
        return API.GET('/api/users/findReaderByName', params)
    },
    //查询获取user列表(通过page分页)
    findReaderList: params => {
        return API.GET('/api/users/findReaderByName', params)
    },
    // 新增角色
    add: params => {
        return API.POST('/api/users/add', params)
    },
    // 修改角色信息
    put: params => {
        return API.POST('/api/users/put', params)
    },
    // 删除角色
    remove: id => {
        return API.DELETE(`/api/users/deleteReaderById/${id}`)
    },
    test: params => {
        return API.POST('/api/users/test', params)
    }
}