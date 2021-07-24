<template>
  <el-row class="warp">
    <el-col :span="24" class="warp-breadcrum">
      <el-breadcrumb separator="/">
        <el-breadcrumb-item :to="{ path: '/home' }">
          <b>首页</b>
        </el-breadcrumb-item>
        <el-breadcrumb-item>图书管理</el-breadcrumb-item>
        <el-breadcrumb-item>图书列表</el-breadcrumb-item>
      </el-breadcrumb>
    </el-col>

    <el-col
      :span="24"
      class="warp-main"
      v-loading="loading"
      element-loading-text="拼命加载中"
    >
      <!--工具条-->
      <el-col :span="24" class="toolbar" style="padding-bottom: 0px">
        <el-form :inline="true" :model="filters">
          <el-form-item>
            <el-input
              v-model="filters.bookName"
              placeholder="书名"
              @keyup.enter.native="handleSearch"
            ></el-input>
          </el-form-item>
          <el-form-item>
            <el-button type="primary" v-on:click="handleSearch">查询</el-button>
          </el-form-item>
          <el-form-item>
            <el-button
              type="primary"
              v-if="identity != 'reader'"
              @click="showAddDialog"
              >新增</el-button
            >
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
        <el-table-column type="selection" min-width="10%"></el-table-column>
        <el-table-column type="index" min-width="10%"></el-table-column>
        <el-table-column type="expand" min-width="5%">
          <template slot-scope="props">
            <el-form label-position="left" inline class="demo-table-expand">
              <el-form-item label="[图书简介]">
                <span>{{ props.row.description }}</span>
              </el-form-item>
            </el-form>
          </template>
        </el-table-column>
        <el-table-column
          prop="bookName"
          label="书名"
          sortable
          min-width="20%"
        ></el-table-column>
        <el-table-column
          prop="author"
          label="作者"
          min-width="10%"
          sortable
        ></el-table-column>
        <el-table-column
          prop="publishAt"
          label="出版日期"
          min-width="8%"
          sortable
        ></el-table-column>
        <el-table-column
          prop="bookNum"
          label="剩余数量"
          min-width="8%"
          sortable
        ></el-table-column>
        <el-table-column label="操作" min-width="25%">
          <template slot-scope="scope">
            <el-button size="small" @click="moredetial(scope.$index, scope.row)"
              >详情</el-button
            >
            <el-button
              size="small"
              @click="lend(scope.$index, scope.row)"
              v-if="identity != 'reader'"
              >借书</el-button
            >
            <el-button
              v-if="identity == 'reader'"
              size="small"
              @click="reserve(scope.$index, scope.row)"
              >预约</el-button
            >
            <el-button
              v-if="identity != 'reader'"
              size="small"
              @click="showEditDialog(scope.$index, scope.row)"
              >编辑</el-button
            >
            <el-button
              type="danger"
              v-if="identity != 'reader'"
              @click="delBook(scope.$index, scope.row)"
              size="small"
              >删除</el-button
            >
          </template>
        </el-table-column>
      </el-table>

      <!--工具条-->
      <el-col :span="24" class="toolbar">
        <el-button
          type="danger"
          @click="batchDeleteBook"
          :disabled="this.sels.length === 0"
          >批量删除</el-button
        >
      </el-col>
      <el-pagination
        layout="prev, pager, next"
        @current-change="handleCurrentChange"
        :page-size="10"
        :total="total"
        style="float: right"
      >
      </el-pagination>
      <el-dialog
        title="编辑"
        :visible.sync="editFormVisible"
        :close-on-click-modal="false"
      >
        <el-form
          :model="editForm"
          label-width="100px"
          :rules="editFormRules"
          ref="editForm"
        >
          <el-form-item label="书名" prop="bookName">
            <el-input
              v-model="editForm.bookName"
              auto-complete="off"
            ></el-input>
          </el-form-item>
          <el-form-item label="作者" prop="author">
            <el-input v-model="editForm.author" auto-complete="off"></el-input>
          </el-form-item>
          <el-form-item label="数量" prop="bookNum" :required="true">
            <el-input v-model="editForm.bookNum" auto-complete="off"></el-input>
          </el-form-item>
          <el-form-item label="ISBN" prop="isbn">
            <el-input v-model="editForm.isbn" auto-complete="off"></el-input>
          </el-form-item>
          <el-form-item label="图片" prop="picture">
            <el-upload
              class="avatar-uploader"
              action="https://jsonplaceholder.typicode.com/posts/"
              :show-file-list="false"
              :on-success="uploadEditPic"
            >
              <img
                v-if="editForm.picture"
                :src="editForm.picture"
                class="avatar"
              />
              <i v-else class="el-icon-plus avatar-uploader-icon"></i>
            </el-upload>
          </el-form-item>
          <el-form-item label="出版日期" :required="true">
            <el-date-picker
              type="date"
              placeholder="选择日期"
              v-model="editForm.publishAt"
            ></el-date-picker>
          </el-form-item>
          <el-form-item label="简介" prop="description">
            <el-input
              type="textarea"
              v-model="editForm.description"
              :rows="8"
            ></el-input>
          </el-form-item>
        </el-form>
        <div slot="footer" class="dialog-footer">
          <el-button @click.native="editFormVisible = false">取消</el-button>
          <el-button type="primary" @click.native="editSubmit">提交</el-button>
        </div>
      </el-dialog>

      <el-dialog
        title="详情"
        :visible.sync="moredetialVisible"
        :close-on-click-modal="true"
      >
        <div class="page">
          <topbar></topbar>
          <div class="bookPanelWrap">
            <div class="bookPanel">
              <div class="cover">
                <img :src="info.imgurl" />
              </div>
              <div class="info">
                <h1>{{ info.bookName }}</h1>
                <p>作者：{{ info.author }}</p>
                <p>出版社：{{ info.publishAt }}</p>
                <p>出版日期：{{ info.publishAt }}</p>
                <p class="txt">简介：{{ info.description }}</p>
              </div>
            </div>
            <input type="button" class="likeBtn" value="收藏" />
          </div>
        </div>
      </el-dialog>
      <!--新增界面-->
      <el-dialog
        title="新增"
        :visible.sync="addFormVisible"
        :close-on-click-modal="false"
      >
        <el-form
          :model="addForm"
          label-width="80px"
          :rules="addFormRules"
          ref="addForm"
        >
          <el-form-item label="书名" prop="bookName">
            <el-input v-model="addForm.bookName" auto-complete="off"></el-input>
          </el-form-item>
          <el-form-item label="作者" prop="author">
            <el-input v-model="addForm.author" auto-complete="off"></el-input>
          </el-form-item>
          <el-form-item label="数量" prop="bookNum" :required="true">
            <el-input v-model="addForm.bookNum" auto-complete="off"></el-input>
          </el-form-item>
          <el-form-item label="ISBN" prop="isbn">
            <el-input v-model="addForm.isbn" auto-complete="off"></el-input>
          </el-form-item>
          <el-form-item label="图片" prop="picture">
            <el-upload
              class="avatar-uploader"
              action="https://jsonplaceholder.typicode.com/posts/"
              :show-file-list="false"
              :on-success="uploadAddPic"
            >
              <img
                v-if="addForm.picture"
                :src="addForm.picture"
                class="avatar"
              />
              <i v-else class="el-icon-plus avatar-uploader-icon"></i>
            </el-upload>
          </el-form-item>
          <el-form-item label="出版日期" :required="true">
            <el-date-picker
              type="date"
              placeholder="选择日期"
              v-model="addForm.publishAt"
            ></el-date-picker>
          </el-form-item>
          <el-form-item label="简介" prop="description">
            <el-input
              type="textarea"
              v-model="addForm.description"
              :rows="8"
            ></el-input>
          </el-form-item>
        </el-form>
        <div slot="footer" class="dialog-footer">
          <el-button @click.native="addFormVisible = false">取消</el-button>
          <el-button
            type="primary"
            @click.native="addSubmit"
            :loading="addLoading"
            >提交</el-button
          >
        </div>
      </el-dialog>
    </el-col>
  </el-row>
</template>
<script>
import util from "../../common/util";
import API from "../../api/api_book";

export default {
  props: ["userId", "userName", "identity"],
  data() {
    return {
      filters: {
        bookName: "",
      },
      books: [],
      total: 0,
      page: 1,
      limit: 10,
      loading: false,
      sels: [], //列表选中列

      //编辑相关数据
      editFormVisible: false, //编辑界面是否显示
      editFormRules: {
        bookName: [{ required: true, message: "请输入书名", trigger: "blur" }],
        author: [{ required: true, message: "请输入作者", trigger: "blur" }],
        bookNum: [{ required: true, message: "请输入数量", trigger: "blur" }],
        isbn: [{ required: true, message: "请输入ISBN", trigger: "blur" }],
        picture: [{ required: false, message: "请添加图片", trigger: "blur" }],
        publishAt: [
          { required: true, message: "请选择出版日期", trigger: "blur" },
        ],
        description: [
          { required: true, message: "请输入简介", trigger: "blur" },
        ],
        location: [{ required: true, message: "请输入位置", trigger: "blur" }],
      },
      editForm: {
        bookName: "",
        author: "",
        publishAt: "",
        description: "",
        isbn: "1",
        bookId: 0,
        picture: "",
        bookNum: "",
        location: "",
      },

      //新增相关数据
      addFormVisible: false, //新增界面是否显示
      addLoading: false,
      addFormRules: {
        bookName: [{ required: true, message: "请输入书名", trigger: "blur" }],
        author: [{ required: true, message: "请输入作者", trigger: "blur" }],
        bookNum: [{ required: true, message: "请输入数量", trigger: "blur" }],
        isbn: [{ required: true, message: "请输入ISBN", trigger: "blur" }],
        picture: [{ required: false, message: "请添加图片", trigger: "blur" }],
        publishAt: [
          { required: true, message: "请选择出版日期", trigger: "blur" },
        ],
        description: [
          { required: true, message: "请输入简介", trigger: "blur" },
        ],
      },
      addForm: {
        bookName: "",
        author: "",
        publishAt: "",
        description: "",
        isbn: "",
        bookId: 1,
        picture: "",
        bookNum: "",
        location: "",
      },

      moredetialVisible: false,
      info: {
        bookName: "",
        author: "",
        publishAt: "",
        description: "",
        imgurl: "",
      },
    };
  },
  methods: {
    getRowClass({ row, column, rowIndex, columnIndex }) {
      return "background:#71838d2c;";
    },
    uploadEditPic(res, file) {
      this.editForm.picture = URL.createObjectURL(file.raw);
    },
    uploadAddPic(res, file) {
      this.addForm.picture = URL.createObjectURL(file.raw);
    },
    getFile(event) {
      //todo
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
    lend(index, rowData) {
      let that = this;
      let param = {
        userId: this.userId,
        bookId: rowData.bookId,
      };
      if (rowData.bookNum <= 0) {
        that.$message.warning({
          showClose: true,
          message: "数量不足",
          duration: 2000,
        });
        return;
      }
      that.loading = true;
      API.lend(param).then(
        function (resp) {
          that.loading = false;
          console.log(resp);
          if (resp && parseInt(resp.stateCode) === 0) {
            that.$message.success({
              showClose: true,
              message: resp.stateMsg,
              duration: 1500,
            });
            that.handleSearch();
          } else {
            that.$message.error({
              showClose: true,
              message: resp.stateMsg,
              duration: 1500,
            });
            that.handleSearch();
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
      );
    },
    reserve(index, rowData) {
      let that = this;
      let param = {
        userId: this.userId,
        bookId: rowData.bookId,
      };
      if (rowData.bookNum <= 0) {
        that.$message.warning({
          showClose: true,
          message: "数量不足",
          duration: 2000,
        });
        return;
      }
      that.loading = true;
      API.reserve(param).then(
        function (resp) {
          that.loading = false;
          console.log(resp);
          if (resp && parseInt(resp.stateCode) === 0) {
            that.$message.success({
              showClose: true,
              message: resp.stateMsg,
              duration: 1500,
            });
            that.handleSearch();
          } else {
            that.$message.error({
              showClose: true,
              message: resp.stateMsg,
              duration: 1500,
            });
            that.handleSearch();
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
      );
    },
    search() {
      let that = this;
      let params = {
        page: that.page,
        limit: 10,
        bookName: that.filters.bookName,
      };
      that.loading = true;
      API.findList(params)
        .then(
          function (result) {
            that.loading = false;
            if (result && result.books) {
              that.total = result.total;
              that.books = result.books;
              that.books.map((a) => {
                let time = a.endTime;
                if (time && time.length > 10) a.endTime = time.substr(0, 10);
              });
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
    selsChange: function (sels) {
      this.sels = sels;
    },
    //删除
    delBook: function (index, row) {
      let that = this;
      this.$confirm("确认删除该记录吗?", "提示", { type: "warning" })
        .then(() => {
          that.loading = true;
          API.remove(row.bookId)
            .then(
              function (result) {
                that.loading = false;
                if (result && parseInt(result.stateCode) === 0) {
                  // console.log
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
              debugger;
              that.$message.error({
                showClose: true,
                message: "请求出现异常",
                duration: 2000,
              });
            });
        })
        .catch(() => {});
    },
    //显示编辑界面
    showEditDialog: function (index, row) {
      this.editFormVisible = true;
      this.editForm = Object.assign({}, row);
    },
    //编辑
    editSubmit: function () {
      let that = this;
      this.$refs.editForm.validate((valid) => {
        if (valid) {
          this.loading = true;
          let para = Object.assign({}, this.editForm);
          para.publishAt =
            !para.publishAt || para.publishAt == ""
              ? ""
              : util.formatDate.format(new Date(para.publishAt), "yyyy-MM-dd");
          console.log(para);
          API.update(para)
            .then(
              function (result) {
                that.loading = false;
                if (result && parseInt(result.stateCode) === 0) {
                  that.$message.success({
                    showClose: true,
                    message: result.stateMsg,
                    duration: 2000,
                  });
                  that.$refs["editForm"].resetFields();
                  that.editFormVisible = false;
                  that.search();
                } else {
                  that.$message.error({
                    showClose: true,
                    message: result.stateMsg,
                    duration: 2000,
                  });
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
        }
      });
    },
    showAddDialog: function () {
      // todo
      this.addFormVisible = true;
      this.addForm = {
        bookName: "",
        author: "",
        publishAt: "",
        description: "",
        isbn: "",
        bookId: "",
        picture: "",
        location: "",
        bookNum: "",
      };
    },
    //新增
    addSubmit: function () {
      let that = this;
      this.$refs.addForm.validate((valid) => {
        if (valid) {
          that.loading = true;
          let para = Object.assign({}, this.addForm);
          para.publishAt =
            !para.publishAt || para.publishAt === ""
              ? ""
              : util.formatDate.format(new Date(para.publishAt), "yyyy-MM-dd");
          console.log(para);
          API.add(para)
            .then(
              function (result) {
                that.loading = false;
                if (result && parseInt(result.stateCode) === 0) {
                  that.$message.success({
                    showClose: true,
                    message: result.stateMsg,
                    duration: 2000,
                  });
                  that.$refs["addForm"].resetFields();
                  that.addFormVisible = false;
                  that.search();
                } else {
                  that.$message.error({
                    showClose: true,
                    message: "修改失败",
                    duration: 2000,
                  });
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
        }
      });
    },
    //批量删除
    batchDeleteBook: function () {
      let ids = this.sels.map((item) => item.bookId).toString();
      let that = this;
      this.$confirm("确认删除选中记录吗？", "提示", {
        type: "warning",
      })
        .then(() => {
          that.loading = true;
          API.removeBatch(ids)
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
    moredetial: function (index, row) {
      this.moredetialVisible = true;
      this.info = Object.assign({}, row);
      this.info.imgurl =
        "http://t15.baidu.com/it/u=276844966,1706646454&fm=224&app=112&f=PNG?w=300&h=400&s=54F620720573F38844ED35E503007022";
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

.page {
  width: 100%;
  height: 90%;
  background: linear-gradient(
      to bottom,
      rgba(255, 255, 255, 0.15) 0%,
      rgba(0, 0, 0, 0.15) 100%
    ),
    radial-gradient(
        at top center,
        rgba(255, 255, 255, 0.4) 0%,
        rgba(0, 0, 0, 0.4) 120%
      )
      #989898;
  background-blend-mode: multiply, multiply;
  position: relative;
}
.bookPanelWrap {
  width: 800px;
  margin: 0 auto;
  position: relative;
}
.bookPanel {
  width: 100%;
  min-height: 600px;
  padding: 20px 0;
  color: #ffffff;
  display: flex;
  box-sizing: border-box;
}
.bookPanel .cover img {
  width: 300px;
  height: 400px;
}
.bookPanel .info {
  margin-left: 30px;
}
.bookPanel .info h1 {
  font-size: 32px;
  font-weight: bold;
  line-height: 60px;
}
.bookPanel .info p {
  font-size: 16px;
  line-height: 40px;
}
.bookPanel .info .txt {
  line-height: 30px;
}
.likeBtn {
  width: 24%;
  height: 50px;
  background-color: #f1ca17;
  color: #ffffff;
  border: none;
  border-radius: 5px;
  outline: none;
  position: relative;
  margin-bottom: 5%;
  margin-left: 38%;
  margin-right: auto;
}
.avatar-uploader .el-upload {
  border: 1px dashed #d9d9d9;
  border-radius: 6px;
  cursor: pointer;
  position: relative;
  overflow: hidden;
}
.avatar-uploader .el-upload:hover {
  border-color: #409eff;
}
.avatar-uploader-icon {
  font-size: 28px;
  color: #8c939d;
  width: 178px;
  height: 80px;
  line-height: 178px;
  text-align: center;
  margin-top: 50px;
}
.avatar {
  width: 178px;
  height: 178px;
  display: block;
}
</style>
