<template>
  <el-row class="warp">
    <el-col :span="24" class="warp-breadcrum">
      <el-breadcrumb separator="/">
        <el-breadcrumb-item :to="{ path: '/home' }"
          ><b>首页</b></el-breadcrumb-item
        >
        <el-breadcrumb-item>设置</el-breadcrumb-item>
        <el-breadcrumb-item>修改密码</el-breadcrumb-item>
      </el-breadcrumb>
    </el-col>

    <el-col :span="24" class="warp-main">
      <el-form
        ref="form"
        :model="form"
        :rules="rules"
        label-width="80px"
        class="login-container"
      >
        <el-form-item label="原密码">
          <el-input v-model="form.oldPassword"></el-input>
        </el-form-item>
        <el-form-item label="新密码">
          <el-input v-model="form.newPassword"></el-input>
        </el-form-item>
        <el-form-item label="确认密码">
          <el-input v-model="form.confirmPassword"></el-input>
        </el-form-item>
        <el-form-item>
          <el-button
            type="primary"
            @click="handleChangePassword"
            style="margin-left: 120px"
            >提交</el-button
          >
        </el-form-item>
      </el-form>
    </el-col>
  </el-row>
</template>
<script>
import API from "../../api/api_user";
export default {
  data() {
    return {
      form: {
        oldPassword: "",
        newPassword: "",
        confirmPassword: "",
      },
      rules: {},
    };
  },
  methods: {
    handleChangePassword() {
      this.$message({
        message: "此功能只是让你看看，不会开发！",
        duration: 1500,
      });
      let user = localStorage.getItem("access-user");
      user = JSON.parse(user);
      if (user) {
        if (
          !(
            this.form.oldPassword === "" ||
            this.form.newPassword === "" ||
            this.form.confirmPassword === ""
          )
        ) {
          if (user.password === this.form.oldPassword) {
            if (this.form.oldPassword !== this.form.confirmPassword) {
              user.password = this.form.newPassword;
              let that = this;
              API.changeProfile(user)
                .then(
                  function (result) {
                    that.loading = false;
                    if (result && result.stateCode == 0) {
                      localStorage.setItem("access-user", JSON.stringify(user));
                      that.$message({
                        message: "修改密码成功！",
                        duration: 1500,
                      });
                    } else {
                      console.log(result);
                      that.$message.error({
                        showClose: true,
                        message: result.errmsg || "修改密码失败！",
                        duration: 1500,
                      });
                    }
                  },
                  function (err) {
                    that.loading = false;
                    that.$message.error({
                      showClose: true,
                      message: err.toString(),
                      duration: 1500,
                    });
                  }
                )
                .catch(function (error) {
                  that.loading = false;
                  console.log(error);
                  that.$message.error({
                    showClose: true,
                    message: "请求出现异常",
                    duration: 1500,
                  });
                });
            } else {
              this.$message({
                message: "两次密码输入有误！",
                duration: 1500,
              });
            }
          } else {
            this.$message({
              message: "原密码输入有误！",
              duration: 1500,
            });
          }
        } else {
          this.$message({
            message: "输入信息不能为空！",
            duration: 1500,
          });
        }
      } else {
        this.$message({
          message: "身份信息失效，请重新登录！",
          duration: 1500,
        });
      }
    },
  },
};
</script>

</style>
<style lang="scss" scoped>
.login-container {
  /*box-shadow: 0 0px 8px 0 rgba(0, 0, 0, 0.06), 0 1px 0px 0 rgba(0, 0, 0, 0.02);*/
  -webkit-border-radius: 5px;
  border-radius: 40px;
  -moz-border-radius: 5px;
  background-clip: padding-box;
  margin: 160px auto;
  width: 500px;
  padding: 35px 35px 15px 35px;
  // background: #fff;
  border: 1px solid #d5e1e7;
  box-shadow: 0 0 25px #b8ebe2;

  background-image: linear-gradient(-225deg, #ee9aee 0%, #94ebe9 100%);

  background: -ms-linear-gradient(top, #ace, #00c1de); /* IE 10 */
  background: -moz-linear-gradient(top, #ace, #00c1de); /*火狐*/
  background: -webkit-gradient(
    linear,
    0% 0%,
    0% 100%,
    from(#ace),
    to(#00c1de)
  ); /*谷歌*/
  background: -webkit-linear-gradient(
    top,
    #ace,
    #00c1de
  ); /*Safari5.1 Chrome 10+*/
  background: -o-linear-gradient(top, #ace, #00c1de); /*Opera 11.10+*/

  .title {
    margin: 0px auto 40px auto;
    text-align: center;
    color: #505458;
  }
  .remember {
    margin: 0px 0px 35px 0px;
  }
}
.input {
  text-align: center;
  border-radius: 5px;
}
.warp-main {
  background-image: linear-gradient(-225deg, #f3e1f3 0%, #d7fffe 100%);
}
</style>