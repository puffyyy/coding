<template>
  <el-row class="warp">
    <el-col :span="24" class="warp-breadcrum">
      <el-breadcrumb separator="/">
        <el-breadcrumb-item :to="{ path: '/home' }"
          ><b>首页</b></el-breadcrumb-item
        >
        <el-breadcrumb-item>用户列表</el-breadcrumb-item>
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
              v-model="filters.name"
              placeholder="用户名/姓名/昵称"
              style="min-width: 240px"
              @keyup.enter.native="search"
            ></el-input>
          </el-form-item>
          <el-form-item>
            <el-button type="primary" @click="search">查询</el-button>
            <el-button
              type="primary"
              @click="showAddDialog"
              v-if="identity === 'staff'"
              >添加</el-button
            >
          </el-form-item>
        </el-form>
      </el-col>

      <!--列表-->
      <div class="table_div">
        <el-table
          class="table"
          :data="users"
          highlight-current-row
          v-loading="loading"
          style="width: 100%; font-size: 20px"
          :row-style="getRowClass"
          :header-row-style="getRowClass"
          :header-cell-style="getRowClass"
        >
          <el-table-column type="index" width="60"> </el-table-column>
          <el-table-column prop="userName" label="姓名" width="120" sortable>
          </el-table-column>
          <el-table-column prop="identity" label="角色" width="120" sortable>
          </el-table-column>
          <el-table-column prop="email" label="邮箱" min-width="160" sortable>
          </el-table-column>
          <el-table-column label="操作" width="150">
            <template slot-scope="scope">
              <el-button
                size="small"
                :disabled="identity != 'staff'"
                @click="showEditDialog(scope.$index, scope.row)"
                >编辑</el-button
              >
              <el-button
                type="danger"
                :disabled="identity != 'staff'"
                @click="deleteUser(scope.$index, scope.row)"
                size="small"
                >删除</el-button
              >
            </template>
          </el-table-column>
        </el-table>
      </div>
      <!--工具条-->
      <el-col :span="24" class="toolbar" v-show="users.length >= 10">
        <el-pagination
          layout="prev, pager, next"
          @current-change="handleCurrentChange"
          :page-size="10"
          :total="total"
          style="float: right"
        >
        </el-pagination>
      </el-col>

      <!--新增界面-->
      <el-dialog
        :title="title"
        :visible.sync="addFormVisible"
        :close-on-click-modal="false"
      >
        <el-form
          :model="addForm"
          label-width="80px"
          :rules="addFormRules"
          ref="addForm"
        >
          <el-form-item label="用户名" prop="userName">
            <el-input v-model="addForm.userName" auto-complete="off"></el-input>
          </el-form-item>
          <el-form-item label="密码" prop="password">
            <el-input
              type="password"
              v-model="addForm.password"
              auto-complete="off"
            ></el-input>
          </el-form-item>
          <el-form-item label="角色" prop="identity">
            <el-radio-group v-model="addForm.identity">
              <el-radio :label="3">工作人员</el-radio>
              <el-radio :label="6">读者</el-radio>
            </el-radio-group>
          </el-form-item>
          <el-form-item label="邮箱" prop="email">
            <el-input v-model="addForm.email" auto-complete="off"></el-input>
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
import API from "../../api/api_user";

export default {
  props: ["nickname"],
  data() {
    return {
      filters: {
        name: "",
      },
      loading: false,
      users: [],
      total: 0,
      page: 1,
      limit: 10,
      title: "新增角色",
      loading: false,
      identity: localStorage.getItem("identity"),
      //新增相关数据
      addFormVisible: false, //新增界面是否显示
      addLoading: false,
      addFormRules: {
        userName: [
          { required: true, message: "请输入用户名", trigger: "blur" },
        ],
        identity: [{ required: true, message: "请选择角色", trigger: "blur" }],
        password: [{ required: true, message: "请输入密码", trigger: "blur" }],
        email: [
          { required: true, message: "请输入邮箱", trigger: "blur" },
          {
            type: "email",
            message: "请输入正确的邮箱地址",
            trigger: "blur,change",
          },
        ],
      },
      addForm: {
        userId: "",
        isAdd: true,
        userName: "",
        password: "",
        identity: "staff",
        email: "",
      },
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
    showEditDialog(index, rowData) {
      this.addFormVisible = true;
      if (rowData) {
        this.title = "修改角色信息";
        this.addForm = {
          userId: rowData.userid,
          userName: rowData.userName,
          password: rowData.password,
          identity: rowData.identity,
          email: rowData.email,
        };
        console.log(rowData);
        if (rowData.identity === "staff") {
          this.$set(this.addForm, "identity", 3);
        } else if (rowData.identity === "reader") {
          this.$set(this.addForm, "identity", 6);
        } else {
          this.$set(this.addForm, "identity", 9);
        }
      } else {
        this.addForm = {
          userId: "",
          isAdd: true,
          userName: "",
          password: "",
          identity: 6,
          email: "",
        };
      }
    },
    showAddDialog(index, rowData) {
      this.addFormVisible = true;
      if (rowData) {
        this.title = "新增角色";
        this.addForm = {
          userId: rowData.userid,
          userName: rowData.userName,
          password: rowData.password,
          identity: rowData.identity,
          email: rowData.email,
        };
        console.log(rowData);
        if (rowData.identity === "staff") {
          this.$set(this.addForm, "identity", 3);
        } else if (rowData.identity === "reader") {
          this.$set(this.addForm, "identity", 6);
        } else {
          this.$set(this.addForm, "identity", 9);
        }
      } else {
        this.addForm = {
          userId: "",
          isAdd: true,
          userName: "",
          password: "",
          identity: 6,
          email: "",
        };
      }
    },
    addSubmit() {
      let flag = false;
      let that = this;
      flag = this.addForm.userid === "" ? false : true;
      this.$refs.addForm.validate((valid) => {
        if (valid) {
          this.addForm.identity == 6
            ? (this.addForm.identity = "reader")
            : (this.addForm.identity = "staff");
          that.loading = true;
          let para = Object.assign({}, this.addForm);
          // 新增，调用添加角色接口
          if (para.isAdd) {
            delete para.isAdd;
            if (flag) {
              API.put(para)
                .then(
                  function (result) {
                    debugger;
                    that.loading = false;
                    if (result && result.stateCode === 0) {
                      debugger;
                      that.$message.success({
                        showClose: true,
                        message: "修改成功",
                        duration: 2000,
                      });
                      that.$refs["addForm"].resetFields();
                      that.addFormVisible = false;
                      that.search();
                    } else {
                      that.loading = false;
                      that.$message.error({
                        showClose: true,
                        message: result.stateMsg,
                        duration: 2000,
                      });
                    }
                  },
                  function (error) {
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
            } else {
              API.add(para)
                .then(
                  function (result) {
                    debugger;
                    that.loading = false;
                    if (result && result.stateCode === 0) {
                      debugger;
                      that.$message.success({
                        showClose: true,
                        message: "新增成功",
                        duration: 2000,
                      });
                      that.$refs["addForm"].resetFields();
                      that.addFormVisible = false;
                      that.search();
                    } else {
                      that.loading = false;
                      that.$message.error({
                        showClose: true,
                        message: result.stateMsg,
                        duration: 2000,
                      });
                    }
                  },
                  function (error) {
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
          } else {
            // 更新，调用修改角色信息接口
            API.put(para)
              .then(
                function (result) {
                  that.loading = false;
                  if (result && parseInt(result.stateCode) === 0) {
                    that.$message.success({
                      showClose: true,
                      message: "修改成功",
                      duration: 2000,
                    });
                    that.$refs["addForm"].resetFields();
                    that.addFormVisible = false;
                    that.search();
                  } else {
                    that.loading = false;
                    that.$message.error({
                      showClose: true,
                      message: result.stateMsg,
                      duration: 2000,
                    });
                  }
                },
                function (error) {
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
        }
      });
    },
    deleteUser(index, rowData) {
      let that = this;
      console.log(rowData);
      this.$confirm("确认删除该记录吗?", "提示", {
        type: "warning",
      }).then(() => {
        that.loading = true;
        API.remove(rowData.userid)
          .then(
            function (result) {
              that.loading = false;
              console.log(result.stateCode);
              if (result && parseInt(result.stateCode) === 0) {
                that.$message.success({
                  showClose: true,
                  message: "删除成功",
                  duration: 2000,
                });
                that.search();
              } else {
                that.$message.error({
                  showClose: true,
                  message: "删除失败",
                  duration: 2000,
                });
              }
            },
            function (error) {
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
      });
    },
    //获取用户列表
    search: function () {
      let that = this;
      let params = {
        page: that.page,
        limit: 10,
        name: that.filters.name,
      };
      that.loading = true;
      API.findReaderList(params)
        .then(
          function (result) {
            that.loading = false;
            if (result && result.readers) {
              that.total = result.total;
              that.users = result.readers;
              console.log(that.users);
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
  },

  mounted() {
    var el = document.getElementsByClassName("el-table");
    console.log(el);
    var th = document.getElementsByTagName("th");
    console.log(th);
  },
};
</script>

<style >
.warp-main {
  background-image: linear-gradient(-225deg, #f3e1f3 0%, #d7fffe 100%);
}
.warp {
  background-image: linear-gradient(-225deg, #f3e1f3 0%, #d7fffe 100%);
}
.table_div {
  background-image: linear-gradient(-225deg, #f3e1f3 0%, #d7fffe 100%);
}
.el-table,
.el-table__expanded-cell {
  background-image: linear-gradient(-225deg, #f1baf1 0%, #9fe6e4 100%);
}
.table-wrapper /deep/ .el-table--fit {
  padding: 10px;
}
.table-wrapper /deep/ .el-table,
.el-table__expanded-cell {
  /* background-color: transparent; */
  background-image: linear-gradient(-225deg, #f3e1f3 0%, #d7fffe 100%);
}

.table-wrapper /deep/ .el-table tr {
  /* background-color: transparent ; */
  background-image: linear-gradient(-225deg, #f3e1f3 0%, #d7fffe 100%);
}
.table-wrapper /deep/ .el-table--enable-row-transition .el-table__body td,
.el-table .cell {
  background-image: linear-gradient(-225deg, #f3e1f3 0%, #d7fffe 100%);
  /* background-color: transparent; */
}
</style>
