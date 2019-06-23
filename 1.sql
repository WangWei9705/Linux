
单表查询

查询工资高于500或岗位为MANAGER的雇员，同时还要满足他们的姓名首字母为大写的J
select sal, job from emp
where sal > 500 
or job = 'MANAGER'
and ename like '%J';

按照部门号升序而雇员的工资降序排序
select * from emp order by deptno, sal desc;

使用年薪进行降序排序
select ename, sal*1+ifnull(comm,0) as "年薪" from emp order by "年薪";

显示工资最高的员工的名字和工作岗位
select ename, job from emp where sal = (select max(sal) from emp);

显示工资高于平均工资的员工信息
select *from emp where sal > (select avg(sal) from emp);

显示每个部门的平均工资和最高工资
select deptno, avg(sal), max(sal) from emp group by deptno;

显示平均工资低于2000的部门号和它的平均工资

select deptno, avg(sal) from emp having avg(sal) < 2000;

显示每种岗位的雇员总数，平均工资

select job, count(*) '总数', avg(sal) from emp group by job;

总结：出现"每"字样时需要进行分组  属于多行查询

多表查询
显示雇员名、雇员工资以及所在部门的名字因为上面的数据来自EMP和DEPT表



列出部门名称和这些部门的员工信息，同时列出没有员工的部门
select * from dept left join emp on dept.deptno = emp.deptno;    左连
select dname, ename from emp right join dept on emp.deptno = dept.deptno;       右连	


索引：提高检索速度，以空间换时间
索引的建立
	主键索引、唯一键索引建立：
		1、直接在声明字段时建立
		2、在语句末尾建立
		3、表建完后使用alter table 表名 add 建立
		
	主键、唯一键特点对比：
	1、一个表只能有一个主键（可符合），可以有多个唯一键
	2、查询效率高
	3、创建主键索引的列的值不能为null，且不能重复；创建唯一键索引的列的值不能重复；如果唯一键值设置为not null 自动转化为主键
	4、主键索引基本都是int类型
		
	普通索引的建立：
		1、在定义表语句末尾 index(需要建立索引的字段);
		2、使用alter table 表名 add index(需要建立索引的字段);
		3、	create index index_name on 表名(需要建立索引的字段);
		
	普通索引一个表中可以拥有多个，如果某列需要建立索引时存在重复值，则需要使用普通索引
		
	查看索引：
		1、show keys from  表名
		2、show index from 表名
		3、desc 表名
		
	全文索引（MYISAM引擎支持全文索引）
	
	删除索引：
		1、alter table 表名 drop primary key;
		2、alter table 表名 drop index index_name;
		3、drop index index_name on 表名；
		
	注意事项：
		1、
		
		
		
事务




视图
	1、视图的创建：create view view_name as select 语句
	2、视图的使用：select * from view_name'


用户权限

