/**
 * Created by guxin on 2018/09/13.
 * 图书相关api
 */
import * as API from './'

export default {

    //查询获取book列表(通过page分页)
    findList: params => {
        return API.GET('/api/books', params)
    },
    //
    findByReader: id => {
        return API.GET(`/api/books/${id}`)
    },

    //查询获取一条book信息
    findById: id => {
        return API.GET(`/api/books/${id}`)
    },

    add: params => {
        return API.POST(`/api/books`, params)
    },
    update: (params) => {
        return API.POST(`/api/books/update`, params)
    },

    //单个删除book
    remove: id => {
        return API.DELETE(`/api/books/${id}`)
    },

    //批量删除，传ids数组
    removeBatch: (ids) => {
        return API.DELETE(`/api/books/batch/${ids}`)
    },
    // 借书
    lend: (params) => {
        return API.POST('/api/books/lend', params)
    },
    // 查询已借书籍
    queryLendBooks: (params) => {
        return API.POST('/api/books/queryLendBooks', params);
    },
    // 还书
    returnBook: (params) => {
        return API.POST('api/books/returnBook', params)
    },
    // 续借
    renew: (params) => {
        return API.POST('api/books/renew', params)
    },
    //查询已预约图书
    findReserveBooks: (params) => {
        return API.POST('api/books/queryReserveBooks', params)
    },
    reserve: (params) => { return API.POST('api/books/reserve', params) },
    cancelReserve: (params) => { return API.POST('api/books/cancelReserve', params) },
    agreeReserve: (params) => { return API.POST('api/books/agreeReserve', params) },
    batchAgreeReserve: (params) => { return API.POST(`/api/books/batch/${params}`) },
    batchCancelReserve: (params) => { return API.POST(`/api/books/batchCancelReserve/${params}`) },
}