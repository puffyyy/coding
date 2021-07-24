<template>
  <el-row class="warp">
    <el-col :span="24" class="warp-breadcrum">
      <el-breadcrumb separator="/">
        <el-breadcrumb-item :to="{ path: '/home' }"
          ><b>首页</b></el-breadcrumb-item
        >
        <el-breadcrumb-item>图书管理</el-breadcrumb-item>
        <el-breadcrumb-item>还书管理</el-breadcrumb-item>
      </el-breadcrumb>
    </el-col>

    <!--列表-->
    <el-table
      :data="books"
      highlight-current-row
      style="width: 100%; font-size: 20px"
      :row-style="getRowClass"
      :header-row-style="getRowClass"
      :header-cell-style="getRowClass"
    >
      <el-table-column type="selection" width="55"></el-table-column>
      <el-table-column type="index" width="60"></el-table-column>
      <!-- <el-table-column type="expand">
        <template slot-scope="props">
          <el-form label-position="left" inline class="demo-table-expand">
            <el-form-item label="[图书简介]">
              <span>{{ props.row.description }}</span>
            </el-form-item>
          </el-form>
        </template>
      </el-table-column> -->
      <el-table-column prop="bookname" label="书名" sortable></el-table-column>
      <el-table-column
        prop="author"
        label="作者"
        width="100"
        sortable
      ></el-table-column>
      <el-table-column
        prop="endTime"
        label="应还日期"
        width="150"
        sortable
      ></el-table-column>
      <el-table-column
        prop="status"
        label="书籍状态"
        width="150"
        sortable
      ></el-table-column>
      <el-table-column label="操作" width="150" prop="bookStatus">
        <template slot-scope="scope">
          <el-button
            size="small"
            @click="returnBook(scope.$index, scope.row)"
            :disabled="scope.row.bookStatus == 2 || scope.row.bookStatus == 3"
            >还书</el-button
          >
          <el-button
            size="small"
            @click="renew(scope.$index, scope.row)"
            :disabled="scope.row.bookStatus == 2 || scope.row.bookStatus == 3"
            >续借</el-button
          >
        </template>
      </el-table-column>
    </el-table>
  </el-row>
</template>
<script>
import util from "../../common/util";
import API from "../../api/api_book";
export default {
  props: ["userId", "userName"],
  data() {
    return {
      books: [],
    };
  },
  methods: {
    getRowClass({ row, column, rowIndex, columnIndex }) {
      return "background:#71838d2c;";
    },
    queryLendBooks(userId) {
      let params = { userId: userId };
      let that = this;

      API.queryLendBooks(params).then(
        function (result) {
          that.books = result.books;
          that.books.map(that.parseData);
          that.books.map((a) => {
            let time = a.endTime;
            if (time.length > 10) a.endTime = time.substr(0, 10);
          });
          that.books.sort(that.cmpbook);
        },
        function (error) {
          that.$message.error({
            showClose: true,
            message: err.toString(),
            duration: 2000,
          });
        }
      );
    },
    returnBook(index, book) {
      let params = {
        userId: this.userId,
        bookId: book.bookId,
        borrowId: book.borrowId,
      };
      let that = this;
      API.returnBook(params).then(
        function (result) {
          that.books = result.books;
          that.books.map(that.parseData);
          that.books.map((a) => {
            let time = a.endTime;
            if (time.length > 10) a.endTime = time.substr(0, 10);
          });
          that.books.sort(that.cmpbook);
          that.$message.success({
            showClose: true,
            message: "还书成功",
            duration: 1500,
          });
        },
        function () {}
      );
    },
    renew(index, book) {
      let params = {
        userId: this.userId,
        bookId: book.bookId,
        borrowId: book.borrowId,
      };
      let that = this;
      API.renew(params).then(
        function (result) {
          if (result && result.stateCode == 0) {
            that.books = result.books;
            that.books.map(that.parseData);
            that.books.map((a) => {
              let time = a.endTime;
              if (time.length > 10) a.endTime = time.substr(0, 10);
            });
            that.books.sort(that.cmpbook);
            that.$message.success({
              showClose: true,
              message: "续借成功",
              duration: 1500,
            });
          } else {
            that.$message.error({
              showClose: true,
              message: result.stateMsg,
              duration: 1500,
            });
          }
        },
        function () {}
      );
    },
    cmpbook(a, b) {
      if (a.bookStatus === b.bookStatus) {
        return a.borrowId - b.borrowId;
      } else {
        return a.bookStatus - b.bookStatus;
      }
    },
    parseData(book) {
      if (book.bookStatus == 0) book.status = "超期未归还";
      else if (book.bookStatus == 1) book.status = "未归还";
      else if (book.bookStatus == 2) book.status = "已归还";
      else if (book.bookStatus == 3) book.status = "超期归还";
    },
  },
  mounted() {
    this.queryLendBooks(this.userId);
  },
};
</script>
<style>
.el-table .cell {
  text-align: center;
}
</style>

