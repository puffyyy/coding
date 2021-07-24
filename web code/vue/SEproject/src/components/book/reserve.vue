<template>
  <el-row class="warp">
    <el-col :span="24" class="warp-breadcrum">
      <el-breadcrumb separator="/">
        <el-breadcrumb-item :to="{ path: '/home' }">
          <b>首页</b>
        </el-breadcrumb-item>
        <el-breadcrumb-item>图书管理</el-breadcrumb-item>
        <el-breadcrumb-item>预约列表</el-breadcrumb-item>
      </el-breadcrumb>
    </el-col>

    <el-col
      :span="24"
      class="warp-main"
      v-loading="loading"
      element-loading-text="拼命加载中"
    >
      <!--工具条-->
      <el-col :span="24" class="toolbar" style="padding-bottom: 0px" v-if="identity!='reader'">
        <el-form :inline="true" :model="filters">
          <el-form-item>
            <el-input
              v-model="filters.name"
              placeholder="用户id"
              @keyup.enter.native="handleSearch"
            ></el-input>
          </el-form-item>
          <el-form-item>
            <el-button type="primary" v-on:click="handleSearch">查询</el-button>
          </el-form-item>
        </el-form>
      </el-col>

      <!--列表-->
      <el-table
        :data="books"
        highlight-current-row
        @selection-change="selsChange"
        style="width: 100%; font-size: 20px"
        :row-style="getRowClass"
        :header-row-style="getRowClass"
        :header-cell-style="getRowClass"
      >
        <el-table-column type="selection" width="55"></el-table-column>
        <el-table-column type="index" width="60"></el-table-column>
        <el-table-column type="expand">
          <template slot-scope="props">
            <el-form label-position="left" inline class="demo-table-expand">
              <el-form-item label="[图书简介]">
                <span>{{ props.row.description }}</span>
              </el-form-item>
            </el-form>
          </template>
        </el-table-column>
        <el-table-column
          prop="bookname"
          label="书名"
          sortable
        ></el-table-column>
        ><el-table-column
          prop="userId"
          label="读者ID"
          sortable
        ></el-table-column>
        <el-table-column
          prop="userName"
          label="读者"
          sortable
        ></el-table-column>
        <el-table-column
          prop="endTime"
          label="截止日期"
          sortable
        ></el-table-column>
        <el-table-column label="操作" width="220">
          <template slot-scope="scope">
            <el-button
              size="small"
              v-if="identity == 'reader'"
              :disabled="scope.row.isLended"
              @click="cancelReserve(scope.$index, scope.row)"
              >取消预约</el-button
            >
            <el-button
              size="small"
              v-if="identity != 'reader'"
              :disabled="scope.row.isLended"
              @click="agreeReserve(scope.$index, scope.row)"
              >同意预约</el-button
            >
          </template>
        </el-table-column>
      </el-table>

      <!--工具条-->
      <el-col :span="24" class="toolbar">
        <el-button
          v-if="identity != 'reader'"
          type="danger"
          @click="batchAgressReserve"
          :disabled="this.sels.length === 0"
          >批量同意预约</el-button
        >
        <el-button
          v-if="identity == 'reader'"
          type="danger"
          @click="batchCancelReserve"
          :disabled="this.sels.length === 0"
          >批量取消预约</el-button
        >
      </el-col>
    </el-col>
  </el-row>
</template>
<script>
import util from "../../common/util";
import API from "../../api/api_book";

export default {
  props: ["userName", "identity", "userId"],
  data() {
    return {
      filters: {
        name: "",
      },
      books: [],
      total: 0,
      loading: false,
      sels: [], //列表选中列
    };
  },
  methods: {
    getRowClass({ row, column, rowIndex, columnIndex }) {
      return "background:#71838d2c;";
    },
    handleCurrentChange(val) {
      this.page = val;
      this.search();
    },
    handleSearch() {
      this.total = 0;
      this.page = 1;
      this.search();
    },
    search() {
      let that = this;
      let params = {
        userId: this.filters.name, //搜索的id
      };
      if(that.identity === 'reader')
        params.userId = this.userId;
      console.log(params)
      that.loading = true;
      API.findReserveBooks(params)
        .then(
          function (result) {
            that.loading = false;
            if (result && result.books) {
              that.books = result.books;
              that.books.map((a) => {
                let time = a.endTime;
                if (time.length > 10) a.endTime = time.substr(0, 10);
              });
              console.log(that.books);
            }
          },
          function (err) {
            that.loading = false;
            that.$message.error({
              showClose: true,
              message: err.toString(),
              duration: 2000,
            });
          }
        )
        .catch(function (error) {
          that.loading = false;
          console.log(error);
          that.$message.error({
            showClose: true,
            message: "请求出现异常",
            duration: 2000,
          });
        });
    },
    agreeReserve(index, rowData) {
      let param = {
        borrowId: rowData.borrowId,
      };
      let that = this;
      that.loading = true;
      API.agreeReserve(param).then(function (resp) {
        that.loading = false;
        if (resp && resp.stateCode === 0) {
          that.$message.success({
            showClose: true,
            message: "同意预约成功",
            duration: 1500,
          });
          that.handleSearch();
        } else {
          that.$message.error({
            showClose: true,
            message: "同意预约失败",
            duration: 1500,
          });
        }
      });
    },
    selsChange: function (sels) {
      this.sels = sels;
    },
    //批量同意预约
    batchAgreeReserve: function () {
      let ids = this.sels.map((item) => item.borrowId).toString();
      let that = this;
      this.$confirm("确认同意选中预约记录吗？", "提示", {
        type: "warning",
      })
        .then(() => {
          that.loading = true;
          API.batchAgreeReserve(ids)
            .then(
              function (result) {
                that.loading = false;
                if (result && parseInt(result.stateCode) === 0) {
                  that.$message.success({
                    showClose: true,
                    message: result.stateMsg,
                    duration: 1500,
                  });
                  that.search();
                }
              },
              function (err) {
                that.loading = false;
                that.$message.error({
                  showClose: true,
                  message: err.toString(),
                  duration: 2000,
                });
              }
            )
            .catch(function (error) {
              that.loading = false;
              console.log(error);
              that.$message.error({
                showClose: true,
                message: "请求出现异常",
                duration: 2000,
              });
            });
        })
        .catch(() => {});
    },
    cancelReserve(index, rowData) {
      let param = {
        borrowId: rowData.borrowId,
      };
      let that = this;
      that.loading = true;
      API.cancelReserve(param).then(function (resp) {
        that.loading = false;
        if (resp && parseInt(resp.stateCode) === 0) {
          that.$message.success({
            showClose: true,
            message: resp.stateMsg || "取消成功",
            duration: 1500,
          });
          that.handleSearch();
        } else {
          that.$message.error({
            showClose: true,
            message: resp.stateMsg,
            duration: 1500,
          });
        }
      });
    },
    batchCancelReserve: function () {
      let ids = this.sels.map((item) => item.borrowId).toString();
      let that = this;
      this.$confirm("确认取消选中预约记录吗？", "提示", {
        type: "warning",
      })
        .then(() => {
          that.loading = true;
          API.batchCancelReserve(ids)
            .then(
              function (result) {
                that.loading = false;
                if (result && parseInt(result.stateCode) === 0) {
                  that.$message.success({
                    showClose: true,
                    message: result.stateMsg || "取消成功",
                    duration: 1500,
                  });
                  that.search();
                }
              },
              function (err) {
                that.loading = false;
                that.$message.error({
                  showClose: true,
                  message: err.toString(),
                  duration: 2000,
                });
              }
            )
            .catch(function (error) {
              that.loading = false;
              console.log(error);
              that.$message.error({
                showClose: true,
                message: "请求出现异常",
                duration: 2000,
              });
            });
        })
        .catch(() => {});
    },
  },
  mounted() {
    this.handleSearch();
  },
};
</script>

<style>
.demo-table-expand label {
  font-weight: bold;
}
.el-table .cell {
  text-align: center;
}
</style>
